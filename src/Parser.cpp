#include "SerialGCodeParser.h"

void SerialGCodeParser::_parse(String command) {
  // Nothing to see here, scroll down. A lot.
  if (command.startsWith("G1")) {
    _g1(command[1], command.substring(2).toInt());
  } else if (command.startsWith("G2")) {
    _g2();
  } else if (command.startsWith("G3")) {
    _g3();
  } else if (command.startsWith("G4")) {
    _g4();
  } else if (command.startsWith("M54")) {
    _m54();
  } else if (command.startsWith("M56")) {
    _m56();
  } else if (command.startsWith("M57")) {
    _m57();
  } else if (command.startsWith("M60")) {
    _m60();
  } else if (command.startsWith("M61")) {
    _m61();
  } else if (command.startsWith("M98")) {
    _m98();
  } else if (command.startsWith("G9")) {
    _g9();
  } else if (command.startsWith("G17")) {
    _g17();
  } else if (command.startsWith("G18")) {
    _g18();
  } else if (command.startsWith("G19")) {
    _g19();
  } else if (command.startsWith("G90")) {
    _g90();
  } else if (command.startsWith("G91")) {
    _g91();
  } else if (command.startsWith("G92")) {
    _g92();
  } else if (command.startsWith("M00")) {
    _m00();
  } else if (command.startsWith("M01")) {
    _m01();
  } else if (command.startsWith("M09")) {
    _m09();
  } else if (command.startsWith("M13")) {
    _m13();
  } else if (command.startsWith("M16")) {
    _m16();
  } else if (command.startsWith("M17")) {
    _m17();
  } else if (command.startsWith("M29")) {
    _m29();
  } else if (command.startsWith("M30")) {
    _m30();
  } else if (command.startsWith("M38")) {
    _m38();
  } else if (command.startsWith("M39")) {
    _m39();
  } else if (command.startsWith("M40")) {
    _m40();
  } else if (command.startsWith("M41")) {
    _m41();
  } else if (command.startsWith("M52")) {
    _m52();
  } else if (command.startsWith("M53")) {
    _m53();
  } else if (command.startsWith("M54")) {
    _m54();
  } else if (command.startsWith("M55")) {
    _m55();
  } else if (command.startsWith("M56")) {
    _m56();
  } else if (command.startsWith("M57")) {
    _m57();
  } else if (command.startsWith("M60")) {
    _m60();
  } else if (command.startsWith("M61")) {
    _m61();
  } else if (command.startsWith("M98")) {
    _m98();
  } else {
    Serial.println("Unknown command: " + command);
  }
}