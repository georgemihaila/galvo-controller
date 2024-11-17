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
  while (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    while (Serial.available() > 0) {
      command += "\n" + Serial.readStringUntil('\n');
    }
    int start = 0;
    int end = command.indexOf('\n');
    while (end != -1) {
      String singleCommand = command.substring(start, end);
      Serial.println(singleCommand);
      _parse(singleCommand);
      start = end + 1;
      end = command.indexOf('\n', start);
    }
    // Handle the last command if there is no trailing newline
    if (start < command.length()) {
      String singleCommand = command.substring(start);
      Serial.println(singleCommand);
      _parse(singleCommand);
    }
  }
  _galvo->tick();
}
