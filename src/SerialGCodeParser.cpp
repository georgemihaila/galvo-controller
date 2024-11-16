#include "SerialGCodeParser.h"

SerialGCodeParser::SerialGCodeParser(int baudRate, XY2_100 *galvo) {
  _baudRate = baudRate;
  _galvo = galvo;

  Serial.begin(_baudRate);
}

void SerialGCodeParser::listen() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    _parse(command);
  } else {
    _galvo->tick();
  }
}

void SerialGCodeParser::_parse(String command) {}