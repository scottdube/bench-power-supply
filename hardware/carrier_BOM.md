# Carrier board — SMD BOM

| RefDes | Part | Package | Qty | Note |
|---|---|---|---|---|
| U4,U5 | AW9523B I/O expander | QFN-24 | 2 | I2C 0x58/0x59 |
| U2,U3 | Auto-dir RS485 xcvr (MAX13487E / equiv) | SOIC-8 | 2 | module<->bus |
| Q2 | AO3400 logic N-MOSFET | SOT-23 | 1 | fan switch |
| K1 | Relay DPDT, 24V coil, ≥5A contacts | THT | 1 | output disconnect/OCP trip |
| K2 | Relay SPST, 24V coil | THT | 1 | aux 24V-raw |
| D1,D2,D5 | SS14 Schottky flyback | SMA(DO-214AC) | 3 | coil/fan flyback |
| BZ1 | Piezo buzzer 3V | THT | 1 | alerts |
| R1-R7 | 10k 1% | 0402 | 7 | AW9523 input pull-ups |
| R8,R9 | 4.7k | 0402 | 2 | I2C pull-ups (DNP unless needed) |
| R10 | 120R | 0805 | 1 | RS485 termination (DNP) |
| Rg | 100R | 0402 | 1 | Q2 gate |
| Rgs | 100k | 0402 | 1 | Q2 gate pulldown |
| C1-C6 | 100nF X7R | 0402 | 6 | IC decoupling |
| C7 | 10uF X5R | 0805 | 1 | bulk on 3V3 |
| J1 | JST-XH 4p | THT | 1 | ESP I2C+3V3 |
| J2 | JST-XH 2p | THT | 1 | ESP RS485 |
| J3,J4 | JST-XH 4p | THT | 2 | module comm |
| J5,J11 | JST-VH 2p | THT | 2 | 24V coil/fan |
| J6 | JST-XH 2p | THT | 1 | ESP DO |
| J7 | JST-XH 3p | THT | 1 | ESP DI passthru |
| J8 | JST-XH 4p | THT | 1 | encoder |
| J9 | JST-XH 5p | THT | 1 | buttons |
| J10 | JST-XH 5p | THT | 1 | status LEDs |
| J12,J13,J14 | Screw terminal 2p, ≥10A | THT | 3 | channel/aux outputs |
| PCB | 2-layer, ~60x80mm, 1.6mm | - | 1 | JLCPCB |