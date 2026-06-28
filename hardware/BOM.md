# Bill of Materials (estimate)

| Qty | Part | Purpose | RefDes | Est. cost |
|---|---|---|---|---|
| 1 | Waveshare ESP32-S3-Touch-LCD-5 (N16R8, 800x480 cap touch) | Controller+display+RS485+isolated IO | U1 | ~$47 |
| 2 | XY6020L buck module (6-70V in, 0-60V/20A, Modbus) | Channel regulators | M1,M2 | ~$58 |
| 2 | TTL<->RS485 transceiver, auto-direction (MAX13487E or module) | Module->bus | U2,U3 | ~$3 |
| 2 | AW9523B I/O expander (0x58, 0x59) | Encoder/buttons/LED/buzzer/fan | U4,U5 | ~$5 |
| 1 | Rotary encoder w/ switch + knob | Fine adjust | ENC1 | ~$3 |
| 4 | Momentary push buttons | Panel controls | SW1-4 | ~$4 |
| 4 | Indicator LEDs | PWR/CC1/CC2/FAULT | LED1-4 | ~$1 |
| 1 | Piezo buzzer | Alerts | BZ1 | ~$1 |
| 2 | Relay, 24V coil (K1 DPDT, K2 SPST) | Disconnect/aux | K1,K2 | ~$4 |
| 5 | Diodes: flyback 1N4007 (D1,D2,D5) + reverse Schottky (D3,D4) | Coil/inductive protect | D1-D5 | ~$2 |
| 2 | TVS diode, standoff just > max Vout | Back-EMF clamp | TVS1,TVS2 | ~$2 |
| 1 | Logic-level N-ch MOSFET | Fan PWM | Q2 | ~$1 |
| 1 | 24V fan | Cooling | FAN1 | ~$5 |
| 2 | Fuse + holder (F1 rail, F2 aux) | Protection | F1,F2 | ~$4 |
| 1 | Rail input connector / terminal block (swap point) | Modular supply | J1 | ~$3 |
| 6 | Binding posts (CH1+/-, CH2+/-, AUX+/-) | Outputs | BP | ~$8 |
| 1 | Retractable lead reel / retractable banana leads | Leads | - | ~$10-20 |
| 1 | 24V supply (S-250-24 on hand; <=36V upgrade later) | Input rail | PS1 | on hand |
| ~ | Pull-up resistors 10k, 0.1uF decoupling, wire, standoffs | Passives/hookup | - | ~$8 |
| 1 | Enclosure (CNC/laser/3DP, your shop) | Chassis | - | ~$10-30 |

**Rough total (excl. supply already on hand): ~$170–210** + enclosure materials.