# Dual-Channel Bench Supply — Feature Spec & Build Matrix

**Platform:** Waveshare ESP32-S3-Touch-LCD-5 (800×480 RGB cap-touch, N16R8) + 2× XY6020L buck modules on an RS-485 Modbus bus, fed from a 24 V rail (S-250-24 on the shelf; ≤36 V swap-friendly upgrade path).
**Date:** 2026-06-23
**Status:** planning / pre-build

---

## Legend

| Tag | Meaning |
|---|---|
| **SW** | Pure firmware — no added parts. Uses hardware already on the board/modules. |
| **HW** | Physical part / mechanical work only. |
| **HW+SW** | Needs an added part *and* firmware to drive it. |

---

## Hardware resource budget (the constraint everything competes for)

The 800×480 RGB panel consumes nearly every raw GPIO, so added features ride on a fixed, small set of interfaces. Allocate deliberately:

- **RS-485 (1 UART, onboard SP3485):** Modbus bus to both XY6020L. *Spoken for.*
- **I²C (onboard, shared):** touch + CH422G + RTC, plus the external terminal → **2× AW9523 expander** (addr 0x58 + 0x59, dodging the CH422G 0x20–0x27 / 0x30–0x3F squat and GT911 0x5D). #1 = encoder(s) + front-panel buttons; #2 = buzzer, status LEDs (AW9523 has per-pin constant-current drive — LEDs need no resistors), fan PWM, spare panel IO. 32 IO total. *Polled (no free INT pin).* Up to 4 chips (0x58–0x5B) possible if ever needed.
- **Isolated digital OUT ×2 (DO0/DO1, 450 mA):** DO0 = output-disconnect relay (hard OFF / OCP trip). DO1 = spare (fan, 2nd relay, or buzzer).
- **Isolated digital IN ×2 (DI0/DI1):** DI0 = lid/e-stop interlock. DI1 = external "start test" trigger.
- **microSD, RTC, WiFi/BLE:** all onboard → "free" for logging/clock/telemetry.

---

## MUST-HAVE (v1 — core function + fixes your current pains)

| Feature | SW/HW | What it needs | Notes |
|---|---|---|---|
| Dual-channel V/I set + readback | **HW+SW** | 2× XY6020L, 2× TTL→RS-485 transceiver, onboard RS-485; Modbus master fw | Core. Addresses 1 & 2 on one bus. |
| Touchscreen dashboard (live V/I/P, CV/CC, on/off) | **SW** | LVGL UI | Display already on board. |
| Effortless adjustment: direct touch entry + set-while-off | **SW** | LVGL numeric entry | Fixes pain #1 (knob fiddling). |
| Encoder fine-adjust w/ digit select | **HW+SW** | rotary encoder on AW9523; input fw | Complements touch entry. |
| One-tap presets (3.3/5/12/24 V; common A) | **SW** | UI | |
| Output on/off independent of setpoint | **SW** | Modbus reg write | XY6020L supports natively. |
| Settable OCP / current limit + clear CC indication | **SW** | Modbus CC reg + UI | Fixes pain #3 (OCP that works). |
| OCP **hard-trip backstop** (true disconnect) | **HW+SW** | relay on DO0; trip-logic fw | Drops load on I>limit; better than foldback-only boxes. |
| Single-rail power, modular & swap-friendly input | **HW** | inline connector/terminal block, fuse holder, fuse | Sized for ≤36 V future supply. |
| Inductive-load output protection | **HW** | TVS (just above Vout max) + reverse diode per channel | For motor/servo back-EMF. |
| Retractable output leads | **HW** | cord-reel or retractable banana leads | Mechanical; your fab. |
| Enclosure (case, panel, binding posts) | **HW** | CNC/laser/3DP case, panel mounts | Your shop. |

---

## SHOULD-HAVE (v1.x — high value, low/moderate effort, mostly firmware)

| Feature | SW/HW | What it needs | Notes |
|---|---|---|---|
| On-screen rolling V/I graphs | **SW** | LVGL chart | |
| SD data logging (timestamped CSV) | **SW** | logger fw | microSD already onboard. |
| RTC-stamped logs / clock | **SW** | use onboard PCF85063 | Real timestamps, survives power loss. |
| Named profile memory (V/I/OCP recall) | **SW** | config store on SD | Unlimited slots vs ~10 on pricey boxes. |
| WiFi telemetry + web UI (view/control) | **SW** | onboard WiFi; web server fw | Network-native; no vendor SCPI lock-in. |
| Home Assistant / MQTT + push alerts | **SW** | MQTT client fw | "Burn-in done", "OCP tripped" → phone. |
| mAh / Wh totalizer | **SW** | ∫I·dt in fw | Battery / capacity tests. |
| Soft-start / slew limiting (dV/dt cap) | **SW** | setpoint-stepping fw | Tames inrush. |
| Settings / screen lock | **SW** | UI | Stops accidental bumps. |
| Audible + visual alerts | **HW+SW** | small buzzer on AW9523 (or DO1); fw | CC entry, fault, complete. |

---

## NICE-TO-HAVE (v2 / optional)

| Feature | SW/HW | What it needs | Notes |
|---|---|---|---|
| Scripted list/sequence test profiles | **SW** | profile engine fw | Ramps/steps/dwell; "List mode" for free. |
| Temperature probe + smart fan + thermal trip | **HW+SW** | temp probe + fan drive on DO1/expander; fw | You already think in probes. |
| Lid / e-stop interlock | **HW+SW** | switch on DI0; fw | Opens output relay on open/stop. |
| External start-test trigger | **HW+SW** | foot-switch/fixture on DI1; fw | Hands-free test start. |
| REST API / scripting endpoint | **SW** | HTTP API fw | Automate from Mac Mini. |
| Per-DUT history dashboard | **SW** | stream to Grafana/InfluxDB on Mac Mini | Long-term trends, compare units. |

---

## NOT FEASIBLE on this hardware (documented honestly)

| Feature | Why | Mitigation |
|---|---|---|
| True 4-wire remote sense | XY6020L has no sense terminals | Rough cal only; short retractable leads reduce drop. |
| Galvanically isolated / independent channels | Both modules share one input rail → common ground | Buy a commercial dual supply if you truly need this. |
| Lab-grade accuracy / low noise | Buck switcher, ~0.4%, switching ripple | Fine for motors/logic/LED; not low-noise analog/RF. |

---

## IO allocation summary (so nothing double-books)

| Resource | Assigned to |
|---|---|
| RS-485 UART | Modbus → XY6020L #1 (addr 1) + #2 (addr 2) |
| I²C / AW9523 #1 @ 0x58 | encoder(s), front-panel buttons |
| I²C / AW9523 #2 @ 0x59 | buzzer, status LEDs, fan PWM, spare panel IO |
| DO0 (isolated, 450 mA) | output-disconnect relay (hard OFF / OCP trip) |
| DO1 (isolated, 450 mA) | freed up → real 2nd relay (e.g., aux / 24 V-raw output) |
| DI0 (isolated) | lid / e-stop interlock |
| DI1 (isolated) | external start-test trigger |
| microSD | data + profile + config storage |
| RTC (PCF85063) | log timestamps |
| WiFi/BLE | web UI, MQTT/HA, REST, Grafana stream |

> Resolved by 2× AW9523: buzzer, status LEDs, and fan all live on expander #2, leaving the scarce isolated DO1 free for a real second relay (aux output / 24 V-raw tap). Up to 4 AW9523s (0x58–0x5B) remain available for future panel IO.
