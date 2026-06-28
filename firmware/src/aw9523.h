// aw9523.h — minimal AW9523B driver (I2C). Polled (INT not wired — no free GPIO).
// One instance per chip. #1 = all inputs (encoder+buttons); #2 = outputs.
#pragma once
#include <Arduino.h>
#include <Wire.h>

class AW9523 {
public:
  // registers
  enum Reg : uint8_t {
    IN_P0=0x00, IN_P1=0x01, OUT_P0=0x02, OUT_P1=0x03,
    CFG_P0=0x04, CFG_P1=0x05, GCR=0x11, LEDMODE_P0=0x12, LEDMODE_P1=0x13,
    DIM_BASE=0x20, SOFT_RESET=0x7F,
  };

  bool begin(TwoWire &w, uint8_t addr);
  void reset();
  // direction: bit=1 input, bit=0 output (port 0 only here; extend for P1)
  void configP0(uint8_t dirMask);
  void p0PushPull(bool en);                 // GCR bit4: P0 push-pull vs open-drain
  uint8_t readP0();                          // raw input byte
  void writeP0Bit(uint8_t bit, bool high);
  void ledMode(uint8_t bit, bool ledCurrent);// true=constant-current LED, false=GPIO
  void ledLevel(uint8_t p0bit, uint8_t val); // 0..255 sink current (LED mode)

private:
  TwoWire *_w=nullptr; uint8_t _a=0; uint8_t _outShadow=0xFF;
  void wr(uint8_t r, uint8_t v); uint8_t rd(uint8_t r);
};

// --- Quadrature encoder decoder fed from polled A/B bits ---------------------
class Encoder {
public:
  // call every poll with current A,B levels; returns -1/0/+1 detent delta
  int update(bool a, bool b);
private:
  uint8_t _prev=0; int8_t _accum=0;
};
