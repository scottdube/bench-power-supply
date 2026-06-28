# Retractable Output Lead — Option B (spiral service-loop, no slip ring)

Self-retracting reel for one DC output lead. **No slip ring** — electrical continuity
across the rotating joint is a flat "service-loop" of the cable itself. One reel per
channel; mounts behind the front panel beside that channel's binding posts (lead is
wired in parallel with the posts, so both are live).

Design target: ~1 m usable lead, ≤ ~5 A (your low-current bench use). All numbers are
**parametric** — change `L_out`, `D_drum`, or the spring and the rest recomputes from
the equations below. Pair with the AndyMark am-4666 spring (STEP available) while modeling.

## Governing equations (put these as Fusion user parameters)

```
N_turns      = L_out / (pi * D_drum)                 # drum revolutions to pay out the lead
S_spring     = pi * D_springspool * N_turns           # spring strip travel  → must be ≤ spring extended length
F_lead       = F_spring * (D_springspool / D_drum)    # retract force felt at the lead
L_loop       = N_turns * pi * (D_hub + D_loopOD)/2    # free wire length coiled in the service-loop cavity
```

The trick: putting the spring on a **small** spool coaxial with the big cable drum
keeps spring travel tiny **and** reduces the felt force by the diameter ratio.

### Spring selection (D_drum = 80 mm, N = 4, L_out = 1 m)

| Spring | Force | Ext. length | Use D_springspool | Travel used | **F_lead** | Notes |
|---|---|---|---|---|---|---|
| **McMaster 9293K18 ✅** | **0.93 lbf** | **838 mm** | **30 mm** | **375 mm (45%)** | **0.35 lbf** | **Chosen.** 301 SS, 25k-cycle, STEP. Best force+margin balance. Coil ID 1.07″→idler ~27 mm |
| AndyMark am-4666 | 2.6 lbf | 762 mm | 20 mm | 251 mm (33%) | 0.65 lbf | Most margin; snappier; carbon spring steel |
| McMaster 9293K125 | 0.52 lbf | 635 mm | 40 mm | 503 mm (79%) | 0.26 lbf | Gentlest, but tight travel + may be too weak vs loop friction |

Baseline below uses **9293K18**.

## Baseline parameters

| Parameter | Symbol | Value | Note |
|---|---|---|---|
| Usable lead length | `L_out` | 1000 mm | adjust to taste |
| Cable | — | 2.5 mm OD | silicone 18 AWG 2-core (or 2× 20 AWG) |
| Cable drum OD | `D_drum` | 80 mm | bigger drum = fewer turns = easier service loop |
| Drum revolutions | `N_turns` | **≈ 4.0** | = 1000/(π·80) |
| Drum groove width | `w_drum` | 12 mm | 4 wraps × 2.5 mm single layer + margin |
| Spring spool OD | `D_springspool` | 30 mm | coaxial with drum |
| Spring travel | `S_spring` | **≈ 375 mm** | ≤ 838 mm (9293K18 33″) ✓ 45% used |
| Spring (9293K18) force | `F_spring` | 0.93 lbf | 301 SS, 0.5″×33″, ID 1.07″, OD 1.23″ |
| **Felt retract force** | `F_lead` | **≈ 0.35 lbf (1.6 N)** | comfortable, positive recoil |
| Spring storage idler OD | `D_idler` | 27 mm | ≈ spring natural ID (1.07″); freewheeling post |
| Service-loop hub OD | `D_hub` | 24 mm | inner anchor (rotates w/ drum) |
| Service-loop cavity OD | `D_loopOD` | 90 mm | outer anchor (fixed housing) |
| Service-loop wire length | `L_loop` | **≈ 716 mm** | coiled slack that absorbs the 4 turns |
| Service-loop axial depth | — | 4 mm | cable OD + clearance |
| Axle | — | 6 mm | 2× 626 bearing (6×19×6) |
| Overall reel OD | — | ≈ 100 mm | |
| Overall reel depth | — | ≈ 35 mm | drum 12 + spring 8 + loop 6 + walls |

## Stack-up (back of panel → front), all on one 6 mm axle

1. **Fixed rear housing** — bolts to enclosure floor/standoffs; holds the rear bearing,
   the service-loop **outer (fixed) anchor**, and a 2-pos terminal that joins the bus.
2. **Service-loop cavity** — flat annulus, ~716 mm of the cable's inner length coiled
   here; inner end anchors to the rotating hub, outer end to the fixed housing. This is
   the slip-ring replacement: it just winds/unwinds ±4 turns.
3. **Spring pocket** — `D_springspool` 20 mm powered spool + 16 mm freewheeling storage
   idler; am-4666 strip transfers between them to provide retract torque.
4. **Cable drum** — `D_drum` 80 mm, 12 mm groove; usable lead wraps here and exits the panel.
5. **Heart-cam latch** (optional) — cardioid groove on the drum's front face, fixed
   1.8 mm hardened pin in the cover. Pull-release = lock; short tug = retract.
6. **Front cover / panel** — lead exits a 6 mm grommeted guide hole; a crimp/stop-ball on
   the lead prevents full retraction; lead ends in a banana plug or test clip.

## Heart-cam latch detail (if you want lock-at-length)

- Cardioid groove ~25 mm tall, 2.0 mm wide for a 1.8 mm dowel pin follower.
- Print at 0.12 mm layers (or machine) so the pin rides smoothly.
- Alternative if you skip it: rely on `F_lead` + a light felt/O-ring friction brake —
  simpler, holds position by drag, no click.

## Materials / fab (your shop)

- Drum, housing, cover, spring spool: **PETG or ASA/ABS** (heat tolerance near the supply),
  3–4 perimeters, 40–50% infill on hubs. ASA if it sits in the warm enclosure.
- Cam track: fine-layer print or machine on the Tormach for durability.
- Brass **heat-set inserts** for cover screws; pressed **626** bearings on the axle.
- Axle: 6 mm shoulder bolt or ground rod; retain with E-clips or shaft collars.

## Reel BOM (per channel)

| Qty | Item | Note |
|---|---|---|
| 1 | Constant-force spring | McMaster 9293K18 (0.93 lbf, 33″, 301 SS) |
| 2 | 626 ball bearing | 6×19×6 mm |
| 1 | 6 mm axle (shoulder bolt) + 2 shaft collars | |
| ~1.7 m | Silicone 18 AWG 2-core cable | 1 m usable + ~0.7 m service loop |
| 1 | Panel grommet, 6 mm | lead exit |
| 1 | Banana plug or test clip + lead stop crimp | |
| 1 | 1.8 mm dowel pin | heart-cam follower (if used) |
| — | Heat-set inserts, M3 screws | assembly |
| 3–4 | 3D-printed parts | housing, drum, spring/loop divider, cover |

## Panel integration

- One reel behind each channel's output; lead exits low on the panel, **binding posts
  directly above** for the high-current/direct case. Reel’s inner terminal lands on the
  same channel node as the posts (parallel) — your per-channel OCP + trip relay still
  protect it.
- Leave ~110 mm clear depth behind the panel for the reel + lead service loop.

## Build order — defer the latch

Build **v1 spring-only**: drum + service loop + constant-force spring, no latch. It
always retracts; you hold the lead where you want it or let it stow. Covers ~90% of use.
Add a **flat boss on the drum rim** in the model so the latch is a bolt-on upgrade later:

- Friction thumb-brake (dead simple: a lever that pinches the rim — hold anywhere), or
- Heart-cam latch (printed cardioid groove on the drum face + fixed pin in the cover) if
  you decide you want lock-at-length. The rotary heart-cam is fussy to print well, so
  only commit to it after the spring-only reel is proven.

