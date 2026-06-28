// main.cpp — glue: RS-485 Modbus master to 2× XY6020L, polled AW9523 HMI,
// OCP hard-trip relay, soft-start, thermostatic fan, LVGL hook points.
//
// This is a SKELETON. It compiles in structure but expects:
//   - ModbusMaster (4-xeon)         lib_deps
//   - LVGL + Waveshare ESP32-S3-Touch-LCD-5 BSP (panel/touch/CH422G init)
// Start from Waveshare's LVGL demo, then drop these modules in and replace the
// ui_* / board:: stubs with the BSP calls.
#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "xy6020.h"
#include "aw9523.h"
#include "board_io.h"

// ---- per-channel model ------------------------------------------------------
struct Channel {
  XY6020 drv;
  XY6020::State st;
  float  targetV=5.0f, targetI=1.0f, ocpLimit=2.0f;
  bool   wantOn=false;
  uint32_t overCurrentSince=0;     // for OCP trip timing
};
Channel ch[2];

AW9523 hmiIn, hmiOut;
Encoder enc;

// selection/edit state for the encoder
int    selChan=0;          // 0/1
int    selField=0;         // 0=V,1=I,2=OCP
uint8_t lastBtns=0xFF;

// ---- helpers ----------------------------------------------------------------
void applySetpoints(int c){ ch[c].drv.setVoltage(ch[c].targetV); ch[c].drv.setCurrent(ch[c].targetI); }

void softStartEnable(int c){
  // ramp the CV setpoint up to tame inrush, then enable output
  ch[c].drv.setCurrent(ch[c].targetI);
  for (float v=0; v<ch[c].targetV; v += SOFTSTART_STEP_MV/1000.0f){
    ch[c].drv.setVoltage(v); delay(SOFTSTART_STEP_MS);
  }
  ch[c].drv.setVoltage(ch[c].targetV);
  ch[c].drv.setOutput(true); ch[c].wantOn=true;
}

void ocpHardTrip(){ board::setRelay(DO_RELAY_MAIN,false); /* drop load */ }

// ---- input scan (≈1 kHz) ----------------------------------------------------
void scanInputs(){
  uint8_t p0 = hmiIn.readP0();
  // encoder
  int d = enc.update(p0&(1<<ENC_A_BIT), p0&(1<<ENC_B_BIT));
  if (d){
    float step = (selField==2)?0.05f:0.1f;
    float &val = (selField==0)?ch[selChan].targetV : (selField==1)?ch[selChan].targetI : ch[selChan].ocpLimit;
    val = constrain(val + d*step, 0.0f, (selField==0)?V_MAX:I_MAX);
    if (selField!=2) applySetpoints(selChan);
    // ui_markDirty();
  }
  // buttons: active-low (to GND). detect new presses.
  uint8_t btns = p0;
  auto pressed=[&](uint8_t bit){ return !(btns&(1<<bit)) && (lastBtns&(1<<bit)); };
  if (pressed(BTN1_BIT)){ ch[0].wantOn?ch[0].drv.setOutput(false),ch[0].wantOn=false:softStartEnable(0); }
  if (pressed(BTN2_BIT)){ ch[1].wantOn?ch[1].drv.setOutput(false),ch[1].wantOn=false:softStartEnable(1); }
  if (pressed(BTN3_BIT)){ /* lock toggle */ }
  if (pressed(BTN4_BIT)){ selField=(selField+1)%3; }
  if (pressed(ENC_SW_BIT)){ selChan^=1; }
  lastBtns=btns;
}

// ---- telemetry + protection (≈3 Hz) ----------------------------------------
void pollChannels(){
  for (int c=0;c<2;c++){
    ch[c].drv.poll(ch[c].st);
    // software OCP backstop (in addition to module CC): trip the relay
    if (ch[c].st.online && ch[c].st.iOut > ch[c].ocpLimit){
      if (!ch[c].overCurrentSince) ch[c].overCurrentSince=millis();
      else if (millis()-ch[c].overCurrentSince > OCP_TRIP_MS){ ocpHardTrip(); /*ui_fault(c)*/ }
    } else ch[c].overCurrentSince=0;
    hmiOut.writeP0Bit(c==0?LED_CC1_BIT:LED_CC2_BIT, ch[c].st.cc); // CC indicator
  }
  // thermostatic fan (hysteresis)
  float t=board::heatsinkTempC();
  if (!isnan(t)){ static bool fan=false;
    if (!fan && t>FAN_ON_C) fan=true; else if (fan && t<FAN_OFF_C) fan=false;
    hmiOut.writeP0Bit(FAN_EN_BIT, fan);
  }
  // interlock: open relay if lid/e-stop opens
  if (board::readDI(DI_INTERLOCK)) ocpHardTrip();
}

// ---- LVGL UI hook points (implement against Waveshare panel BSP) ------------
void ui_init();        // build the two-channel dashboard, graphs, presets
void ui_tick();        // push ch[].st into widgets; call lv_timer_handler()

void setup(){
  Serial.begin(115200);
  RS485_UART.begin(RS485_BAUD, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  ch[0].drv.begin(MODBUS_ADDR_CH1, RS485_UART);
  ch[1].drv.begin(MODBUS_ADDR_CH2, RS485_UART);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, 400000);
  hmiIn.begin(Wire, AW9523_IN_ADDR);   hmiIn.configP0(0x7F);          // P0_0..6 inputs
  hmiOut.begin(Wire, AW9523_OUT_ADDR); hmiOut.configP0(0x00);         // all outputs
  hmiOut.p0PushPull(true);
  for (uint8_t b : {LED_PWR_BIT,LED_CC1_BIT,LED_CC2_BIT,LED_FLT_BIT}){ hmiOut.ledMode(b,true); hmiOut.ledLevel(b,40); }

  board::initIsolatedIO();
  board::setRelay(DO_RELAY_MAIN,true);   // arm output path

  for (int c=0;c<2;c++) applySetpoints(c);
  ui_init();
}

void loop(){
  static uint32_t tIn=0, tPoll=0;
  uint32_t now=millis();
  if (now-tIn   >= INPUT_POLL_MS){ tIn=now;   scanInputs(); }
  if (now-tPoll >= POLL_PERIOD_MS){ tPoll=now; pollChannels(); }
  ui_tick();   // lv_timer_handler() inside
}
