#include "xy6020.h"
#include "config.h"

bool XY6020::_read(uint16_t reg, uint16_t &out) {
  if (_node.readHoldingRegisters(reg, 1) != _node.ku8MBSuccess) return false;
  out = _node.getResponseBuffer(0);
  return true;
}
bool XY6020::_write(uint16_t reg, uint16_t val) {
  return _node.writeSingleRegister(reg, val) == _node.ku8MBSuccess;
}

bool XY6020::poll(State &s) {
  uint16_t v;
  // Each read is its own transaction; bail (mark offline) on first failure.
  if (!_read(V_SET, v))   { s.online=false; return false; } s.vSet  = v/100.0f;
  if (!_read(I_SET, v))   { s.online=false; return false; } s.iSet  = v/100.0f;
  if (!_read(VOUT,  v))   { s.online=false; return false; } s.vOut  = v/100.0f;
  if (!_read(IOUT,  v))   { s.online=false; return false; } s.iOut  = v/100.0f;
  if (!_read(POWER, v))   { s.online=false; return false; } s.power = v/10.0f;
  if (!_read(UIN,   v))   { s.online=false; return false; } s.uIn   = v/100.0f;
  if (!_read(ONOFF, v))   { s.online=false; return false; } s.on    = v;
  if (!_read(CVCC,  v))   { s.online=false; return false; } s.cc    = v;
  if (!_read(PROTECT,v))  { s.online=false; return false; } s.protect = v;
  s.online = true;
  return true;
}

bool XY6020::setVoltage(float volts) {
  volts = constrain(volts, 0.0f, V_MAX);
  return _write(V_SET, (uint16_t)lroundf(volts*100));
}
bool XY6020::setCurrent(float amps) {
  amps = constrain(amps, 0.0f, I_MAX);
  return _write(I_SET, (uint16_t)lroundf(amps*100));
}
bool XY6020::setOutput(bool on) { return _write(ONOFF, on?1:0); }

const char* XY6020::protectName(uint16_t c) {
  switch (c) {
    case 0: return "OK";  case 1: return "OVP"; case 2: return "OCP";
    case 3: return "OPP"; case 4: return "LVP"; case 7: return "OTP";
    default: return "FAULT";
  }
}
