// board_io.h — isolated DO/DI via the onboard CH422G expander.
// These are STUBS: wire them to Waveshare's CH422G driver from their
// ESP32-S3-Touch-LCD-5 BSP / LVGL demo (the same lib that brings up the panel,
// touch, and backlight). Kept behind this interface so the rest of the code
// never touches board specifics.
#pragma once
#include <Arduino.h>

namespace board {
  void initIsolatedIO();              // configure CH422G OD0/OD1 out, EXIO0/5 in
  void setRelay(uint8_t idx, bool on);// idx 0=DO_RELAY_MAIN, 1=DO_RELAY_AUX
  bool readDI(uint8_t idx);           // idx 0=interlock, 1=trigger (dry contact)
  float heatsinkTempC();              // optional probe; return NAN if none
}
