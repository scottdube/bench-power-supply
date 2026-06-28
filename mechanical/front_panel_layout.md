# Front Panel Layout — Dual-Channel Bench Supply

Panel face for the build. One 5″ touch display drives both channels (PS1/PS2 shown
side-by-side in the LVGL UI), with a hard-control cluster, status LEDs, and an output
row (binding posts + retractable-reel exits + aux). Mains/fan live on the **rear**.

**Panel size:** 300 mm W × 180 mm H. Material: 3 mm aluminum (CNC) or laser-cut
acrylic/composite. Origin = top-left, all coordinates to hole/cutout **center** in mm.

## Hole / cutout schedule

| Feature | Qty | Size | Center (x, y) | Note |
|---|---|---|---|---|
| Display window | 1 | 110 × 66 cutout | 67, 47 (cutout TL 12,14) | 5″ active 108×64.8; board 112.4×75.1 behind on M3 standoffs |
| Encoder shaft | 1 | ⌀7 | 175, 46 | knob ⌀25 clearance; V/I fine adjust |
| Pushbutton CH1 EN | 1 | ⌀12 | 228, 34 | output on/off ch1 |
| Pushbutton CH2 EN | 1 | ⌀12 | 263, 34 | output on/off ch2 |
| Pushbutton LOCK | 1 | ⌀12 | 228, 70 | settings lock |
| Pushbutton SEL/MENU | 1 | ⌀12 | 263, 70 | select / field cycle |
| LED PWR | 1 | ⌀5 | 150, 96 | green |
| LED CC1 | 1 | ⌀5 | 170, 96 | amber, ch1 in CC |
| LED CC2 | 1 | ⌀5 | 190, 96 | amber, ch2 in CC |
| LED FAULT | 1 | ⌀5 | 210, 96 | red, OCP/trip |
| Binding post CH1 + | 1 | ⌀12 | 40, 132 | red |
| Binding post CH1 − | 1 | ⌀12 | 60, 132 | black (20 mm pair pitch) |
| Binding post CH2 + | 1 | ⌀12 | 105, 132 | red |
| Binding post CH2 − | 1 | ⌀12 | 125, 132 | black |
| Binding post AUX + | 1 | ⌀12 | 185, 132 | "24 V RAW" |
| Binding post AUX − | 1 | ⌀12 | 205, 132 | black |
| Reel exit CH1 | 1 | ⌀8 grommet | 50, 162 | retractable lead |
| Reel exit CH2 | 1 | ⌀8 grommet | 115, 162 | retractable lead |
| Power rocker | 1 | 19 × 13 cutout | 262, 150 | main on/off (see rear note) |

## Behind-panel clearance & enclosure

- **Reels:** mount each disc **parallel to the panel** behind the output row (≈⌀100 each,
  ~35 mm deep), leads routed to their grommets. Two side-by-side ≈ 210 mm wide × 100 tall.
- **Display board:** shallow (~20 mm + FPC); M3 standoffs off the panel.
- **XY6020L ×2:** ~78 × 55 × ~40 mm each (taller with their fans) — on a shelf/bracket.
- **24 V supply (S-250-24):** ~199 × 98 × 38 mm — along the floor at the rear (the depth driver).
- **Estimated enclosure:** ≈ **300 W × 180 H × 250 D mm.** Depth set by the supply length.

## Rear panel (separate layout)

- IEC inlet + fuse + (optional) main mains switch; or feed the supply and use the front rocker.
- 24 V rail input connector J1 (the modular swap point) if the supply lives external.
- Fan exhaust (24 V fan, thermostatic) + finger guard; intake louvers low on a side panel.
- Keep mains wiring fully on the rear, shrouded, away from the low-voltage front harness.

## Notes

- Posts use standard 19.05 mm (¾″) pair pitch → accepts dual banana plugs; I rounded to 20 mm.
- Reel grommet sits ~30 mm below its channel's posts so the retractable lead and a plugged-in
  lead don't fight for space.
- Silk/engrave labels: PS1 / PS2 under the display halves; V·A·OCP by the encoder; post polarity.
- All control I/O (encoder, buttons, LEDs) lands on the 2× AW9523 per the schematic.
