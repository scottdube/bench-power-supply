// xy6020.h — Modbus-RTU driver for one XY6020L on the shared RS-485 bus.
// Register map & scaling taken from the working FireMarshmellow project.
#pragma once
#include <Arduino.h>
#include <ModbusMaster.h>

class XY6020 {
public:
  // XY6020L holding registers
  enum Reg : uint16_t {
    V_SET = 0x0000, I_SET = 0x0001, VOUT = 0x0002, IOUT = 0x0003,
    POWER = 0x0004, UIN = 0x0005, LOCK = 0x000F,
    PROTECT = 0x0010, CVCC = 0x0011, ONOFF = 0x0012, SLAVE_ADD = 0x0018,
  };

  struct State {
    float vSet=0, iSet=0, vOut=0, iOut=0, power=0, uIn=0;
    bool  on=false, cc=false, online=false;
    uint16_t protect=0;          // 0=OK; see protectName()
  };

  void begin(uint8_t address, Stream &serial) { _addr=address; _node.begin(address, serial); }

  bool poll(State &s);                       // read all telemetry into s
  bool setVoltage(float volts);              // CV setpoint (clamped)
  bool setCurrent(float amps);               // CC limit  (clamped)
  bool setOutput(bool on);
  static const char* protectName(uint16_t code);

private:
  ModbusMaster _node;
  uint8_t _addr=1;
  bool _read(uint16_t reg, uint16_t &out);
  bool _write(uint16_t reg, uint16_t val);
};
