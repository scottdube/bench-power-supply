# Bench Supply — ESP32-S3 firmware skeleton

Greenfield firmware for the dual-channel bench supply. Matches `../hardware/schematic.pdf`
and `../FEATURE_SPEC.md`. **Skeleton status:** the hardware-independent logic
(Modbus, AW9523, control loop, OCP trip, soft-start, fan) is written; the
board-specific display/touch/CH422G layer is stubbed for you to wire to
Waveshare's BSP.

## Layout
| File | Role |
|---|---|
| `include/config.h` | All pins, I²C/Modbus addresses, register map, tunables |
| `src/xy6020.{h,cpp}` | Modbus-RTU driver for one XY6020L (poll + set V/I/output) |
| `src/aw9523.{h,cpp}` | AW9523B I²C expander + quadrature encoder decoder |
| `src/board_io.h` | Isolated DO/DI via CH422G — **stub, wire to Waveshare BSP** |
| `src/main.cpp` | Glue: input scan, telemetry poll, OCP trip, fan, UI hooks |

## How the design maps to code
- **Two XY6020L share one RS-485 bus** (onboard SP3485, auto-direction → no DE pin).
  `Serial1` on GPIO44/43, two `XY6020` instances at Modbus addr 1 & 2, polled sequentially.
- **Encoder + buttons** are read by polling AW9523 #1 (0x58) at ~1 kHz (no free GPIO
  for the INT line). The encoder uses a Gray-code state machine, 4 edges/detent.
- **Status LEDs** use AW9523 #2 (0x59) constant-current sink (no series resistors).
- **OCP hard-trip**: in addition to the module's own CC limit, if measured current
  exceeds the per-channel limit for `OCP_TRIP_MS`, `board::setRelay(MAIN,false)`
  physically drops the load (CH422G DO0 → K1).
- **Soft-start** ramps the CV setpoint before enabling output (motor inrush).
- **Fan** is thermostatic ON/OFF with hysteresis (AW9523 has no true PWM).
- **Interlock** (DI0) opens the relay; **trigger** (DI1) is free for test-start.

## To bring it up
1. Clone Waveshare's ESP32-S3-Touch-LCD-5 LVGL demo; confirm the panel + touch run.
2. Add `ModbusMaster` and `lvgl` to `lib_deps`; add the Waveshare BSP.
3. Implement `board_io.h` and `ui_init()/ui_tick()` against the BSP (panel, GT911, CH422G).
4. Set each XY6020L's Modbus address (1 and 2) once, with one module connected.
5. Build/flash over the UART USB-C port.

## Not yet implemented (next steps)
SD/CSV logging, named profiles, WiFi/MQTT→Home Assistant, list/sequence test
profiles, mAh/Wh totalizer, web UI. All firmware-only per the feature matrix.
