// config.h — board/bus/pin map for the dual-channel bench supply
// Target: Waveshare ESP32-S3-Touch-LCD-5 (N16R8). See hardware/schematic.pdf.
#pragma once
#include <Arduino.h>

// ---- RS-485 Modbus bus (onboard SP3485, auto-direction → no DE/RE pin) ------
// Waveshare board: RS485_TXD = GPIO43, RS485_RXD = GPIO44.
#define RS485_UART        Serial1
#define RS485_TX_PIN      43
#define RS485_RX_PIN      44
#define RS485_BAUD        115200
#define MODBUS_ADDR_CH1   1      // XY6020L #1 (set with xy6020l_set_address)
#define MODBUS_ADDR_CH2   2      // XY6020L #2
#define MODBUS_TIMEOUT_MS 150

// ---- I2C (shared onboard bus; touch/CH422G/RTC live here too) ---------------
// SDA=GPIO8, SCL=GPIO9. AW9523 addresses chosen to dodge CH422G(0x20-0x27,
// 0x30-0x3F) and GT911(0x5D).
#define I2C_SDA_PIN       8
#define I2C_SCL_PIN       9
#define AW9523_IN_ADDR    0x58   // U4: encoder + buttons (all inputs)
#define AW9523_OUT_ADDR   0x59   // U5: buzzer, LEDs, fan-enable

// ---- AW9523 #1 (0x58) pin map: P0_x = bit x of port 0 ----------------------
#define ENC_A_BIT   0   // P0_0
#define ENC_B_BIT   1   // P0_1
#define ENC_SW_BIT  2   // P0_2
#define BTN1_BIT    3   // P0_3  CH1 on/off
#define BTN2_BIT    4   // P0_4  CH2 on/off
#define BTN3_BIT    5   // P0_5  lock
#define BTN4_BIT    6   // P0_6  menu/select
// NOTE: AW9523 P-port has no internal pull-up → 10k to 3V3 on each (see schematic note 3).

// ---- AW9523 #2 (0x59) pin map ----------------------------------------------
#define BUZZ_BIT    0   // P0_0  buzzer (GPIO, push-pull: set GCR bit4)
#define LED_PWR_BIT 1   // P0_1  status LEDs use AW9523 constant-current (LED mode)
#define LED_CC1_BIT 2   // P0_2
#define LED_CC2_BIT 3   // P0_3
#define LED_FLT_BIT 4   // P0_4
#define FAN_EN_BIT  5   // P0_5  fan MOSFET gate — ON/OFF only (AW9523 has no real PWM)

// ---- Isolated IO via onboard CH422G (drive through Waveshare BSP) -----------
// DO0 → K1 output-disconnect relay (OCP hard-trip / master off)
// DO1 → K2 aux / 24V-raw relay
// DI0 → lid / e-stop (dry contact);  DI1 → external start trigger (dry contact)
#define DO_RELAY_MAIN   0   // CH422G OD0
#define DO_RELAY_AUX    1   // CH422G OD1
#define DI_INTERLOCK    0   // CH422G EXIO0
#define DI_TRIGGER      1   // CH422G EXIO5

// ---- Control behaviour ------------------------------------------------------
#define POLL_PERIOD_MS     300    // module telemetry poll
#define INPUT_POLL_MS      1      // encoder/button scan (≈1 kHz)
#define OCP_TRIP_MS        200    // I>limit must persist this long to trip relay
#define SOFTSTART_STEP_MV  200    // setpoint ramp step on enable
#define SOFTSTART_STEP_MS  20
#define FAN_ON_C           45.0f  // thermostatic fan hysteresis
#define FAN_OFF_C          38.0f
#define V_MAX              60.0f  // module ceiling; real ceiling = rail − ~2 V
#define I_MAX              20.0f
