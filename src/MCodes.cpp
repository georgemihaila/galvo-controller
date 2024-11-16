#include "SerialGCodeParser.h"

#pragma region M code helpers
void SerialGCodeParser::_set_guide_beam(String laser, bool state) {
#ifdef guide_beam_l1_pin
  if (laser.equalsIgnoreCase("L1")) {
    digitalWrite(guide_beam_l1_pin, state);
  }
#endif
#ifdef guide_beam_l2_pin
  if (laser.equalsIgnoreCase("L2")) {
    digitalWrite(guide_beam_l2_pin, state);
  }
#endif
}

void SerialGCodeParser::_set_branch_shutter(String laser, bool state) {
#ifdef branch_shutter_l1_pin
  if (laser.equalsIgnoreCase("L1")) {
    digitalWrite(branch_shutter_l1_pin, state);
  }
#endif
#ifdef branch_shutter_l2_pin
  if (laser.equalsIgnoreCase("L2")) {
    digitalWrite(branch_shutter_l2_pin, state);
  }
#endif
}

void SerialGCodeParser::_set_water(bool state) {
#ifdef water_pin
  digitalWrite(water_pin, state);
#endif
}

void SerialGCodeParser::_set_collet(bool state) {
#ifdef collet_pin
  digitalWrite(collet_pin, state);
#endif
}

void SerialGCodeParser::_set_gas(bool state) {
#ifdef gas_pin
  digitalWrite(gas_pin, state);
#endif
}

void SerialGCodeParser::_stop() {
  _stopped = true;
  _m55();
}
void SerialGCodeParser::_resume() {
  _stopped = false;
  _m54();
}
#pragma endregion

void SerialGCodeParser::_m56(String laser = "L1") {
  _set_guide_beam(laser, true);
}

void SerialGCodeParser::_m57(String laser = "L1") {
  _set_guide_beam(laser, false);
}

void SerialGCodeParser::_m60(String laser = "L1") {
  _set_branch_shutter(laser, true);
}

void SerialGCodeParser::_m61(String laser = "L1") {
  _set_branch_shutter(laser, false);
}

void SerialGCodeParser::_m98() {
  // Do nothing
}

void SerialGCodeParser::_m54() {
  if (_laser1) {
    _laser1->turnOn();
  }
  if (_laser2) {
    _laser2->turnOn();
  }
}

void SerialGCodeParser::_m55() {
  if (_laser1) {
    _laser1->turnOff();
  }
  if (_laser2) {
    _laser2->turnOff();
  }
}

void SerialGCodeParser::_m30() {
  if (_laser1) {
    _laser1->turnOff();
  }
  if (_laser2) {
    _laser2->turnOff();
  }
  exit(0);
}

void SerialGCodeParser::_m38() { _set_water(true); }

void SerialGCodeParser::_m39() { _set_water(false); }

void SerialGCodeParser::_m40() { _set_collet(true); }

void SerialGCodeParser::_m41() { _set_collet(false); }

void SerialGCodeParser::_m60(String laser) { _set_branch_shutter(laser, true); }

void SerialGCodeParser::_m61(String laser) {
  _set_branch_shutter(laser, false);
}

void SerialGCodeParser::_m16() { _set_gas(true); }
void SerialGCodeParser::_m17() { _set_gas(false); }

void SerialGCodeParser::_m00() { _stop(); }

void SerialGCodeParser::_m01() { _stop(); }

void SerialGCodeParser::_m02() { _resume(); }
