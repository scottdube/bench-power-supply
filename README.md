# bench-power-supply

Dual-channel programmable bench supply built around a **Waveshare ESP32-S3-Touch-LCD-5**
(800×480 cap-touch) driving **2× XY6020L** buck modules over a shared RS-485 Modbus bus,
fed from a 24 V rail. Touch + rotary-encoder control, per-channel V/I set & readback,
hardware OCP-trip relay, soft-start, and an LVGL dashboard — with a roadmap to SD/CSV
logging and Home Assistant telemetry.

**Status:** planning / pre-build. The firmware is a working *skeleton* (Modbus master,
AW9523 HMI, control loop, OCP hard-trip, soft-start, thermostatic fan); the Waveshare
display / touch / CH422G layer is stubbed for the BSP. Full feature and build matrix in
[`FEATURE_SPEC.md`](FEATURE_SPEC.md).

## Layout

| Path | Contents |
|---|---|
| `firmware/` | PlatformIO project (ESP32-S3) — details in [`firmware/README.md`](firmware/README.md) |
| `hardware/` | KiCad schematic, carrier board, BOMs, connection maps |
| `mechanical/` | Enclosure / front-panel / reel specs |
| `redesign/` | Working notes for the next iteration |
| `FEATURE_SPEC.md` | Feature matrix + hardware resource budget |

## Credits / attribution

- **XY6020L Modbus register map & scaling** — adapted from FireMarshmellow's
  [Mellow_Lab_bench_power_supply](https://github.com/FireMarshmellow/Mellow_Lab_bench_power_supply),
  per the note in `firmware/src/xy6020.h`.
- **Board bring-up (RGB panel / GT911 touch / CH422G IO)** — built on **Waveshare's
  ESP32-S3-Touch-LCD-5** BSP and LVGL demo.
- **Libraries** — ModbusMaster (Doc Walker) and [LVGL](https://lvgl.io). The AW9523B
  expander/encoder driver in this repo is original.

## License

Not yet licensed. Add a `LICENSE` before making this public if you want to set explicit
reuse terms (the upstream references above carry their own licenses regardless).
