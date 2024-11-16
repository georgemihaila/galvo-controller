#include "SerialGCodeParser.h"
SerialGCodeParser::SerialGCodeParser(int baudRate, XY2_100 *galvo,
                                     Laser *laser1)
    : SerialGCodeParser(baudRate, galvo, laser1, nullptr) {}

SerialGCodeParser::SerialGCodeParser(int baudRate, XY2_100 *galvo,
                                     Laser *laser1, Laser *laser2) {
  _baudRate = baudRate;
  _galvo = galvo;
  _laser1 = laser1;
  _laser2 = laser2;
  _stopped = false;

  Serial.begin(_baudRate);
  Serial.println("Up");
}

void SerialGCodeParser::listen() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
    _parse(command);
  } else {
    _galvo->tick();
  }
}