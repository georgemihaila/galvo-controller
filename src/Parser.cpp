#include "SerialGCodeParser.h"

// Extract the laser from the command assuming the laser name is the only
// argument
#define _extract_laser_as_only_argument command.substring(3)
#define _extract_xy extractValue('X'), extractValue('Y')

void SerialGCodeParser::_parse(String command) {
  auto extractValue = [&](char identifier) -> double {
    int index = command.indexOf(identifier);
    if (index != -1) {
      int nextIndex = index + 1;
      while (nextIndex < command.length() &&
             (isDigit(command[nextIndex]) || command[nextIndex] == '.' ||
              command[nextIndex] == '-')) {
        nextIndex++;
      }
      return command.substring(index + 1, nextIndex).toDouble();
    }
    if (identifier == 'R') {
      int fIndex = command.indexOf('F');
      if (fIndex != -1) {
        int nextFIndex = fIndex + 1;
        while (nextFIndex < command.length() &&
               (isDigit(command[nextFIndex]) || command[nextFIndex] == '.' ||
                command[nextFIndex] == '-')) {
          nextFIndex++;
        }
        return command.substring(fIndex + 1, nextFIndex).toDouble();
      }
      return 0;
    }
    return 0;
  };
  // Nothing to see here, scroll down. A lot.
  if (command.startsWith("G0")) {
    _g0(_extract_xy);
  } else if (command.startsWith("G1")) {
    _g1(command[3], extractValue(command[3]));
  } else if (command.startsWith("G2")) {
    _g2(_extract_xy, extractValue('I'), extractValue('J'), extractValue('R'));
  } else if (command.startsWith("G3")) {
    _g3(_extract_xy, extractValue('I'), extractValue('J'), extractValue('R'));
  } else if (command.startsWith("G4")) {
    _g4(extractValue('P'));
  } else if (command.startsWith("M54")) {
    _m54();
  } else if (command.startsWith("M56")) {
    _m56(_extract_laser_as_only_argument);
  } else if (command.startsWith("M57")) {
    _m57(_extract_laser_as_only_argument);
  } else if (command.startsWith("M60")) {
    _m60(_extract_laser_as_only_argument);
  } else if (command.startsWith("M61")) {
    _m61(_extract_laser_as_only_argument);
  } else if (command.startsWith("M98")) {
    _m98();
  } else if (command.startsWith("G9")) {
    _g9(_extract_xy);
  } else if (command.startsWith("G17")) {
    _g17();
  } else if (command.startsWith("G18")) {
    _g18();
  } else if (command.startsWith("G19")) {
    _g19();
  }
  // Scroll down for more.
  else if (command.startsWith("G28")) {
    _g28();
  } else if (command.startsWith("G28.1")) {
    _g28p1(_extract_xy);
  } else if (command.startsWith("G90")) {
    _g90();
  } else if (command.startsWith("G91")) {
    _g91();
  } else if (command.startsWith("G92")) {
    _g92(_extract_xy);
  } else if (command.startsWith("M00")) {
    _m00();
  } else if (command.startsWith("M01")) {
    _m01();
  } else if (command.startsWith("M02")) {
    _m02();
  } else if (command.startsWith("M09")) {
    // _m09();
    Serial.println("M09 not suppported");
  } else if (command.startsWith("M13")) {
    double pValue = extractValue('P');
    double fValue = extractValue('F');
    double wValue = extractValue('W');
    _m13(pValue, fValue, wValue);
  } else if (command.startsWith("M16")) {
    _m16();
  } else if (command.startsWith("M17")) {
    _m17();
  } else if (command.startsWith("M29")) {
    //_m29();
    Serial.println("M29 not suppported");
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
    _m52(_extract_laser_as_only_argument);
  } else if (command.startsWith("M53")) {
    _m53(_extract_laser_as_only_argument);
  } else if (command.startsWith("M54")) {
    _m54();
  } else if (command.startsWith("M55")) {
    _m55();
  } else if (command.startsWith("M56")) {
    _m56(_extract_laser_as_only_argument);
  } else if (command.startsWith("M57")) {
    _m57(_extract_laser_as_only_argument);
  } else if (command.startsWith("M60")) {
    _m60(_extract_laser_as_only_argument);
  } else if (command.startsWith("M61")) {
    _m61(_extract_laser_as_only_argument);
  } else if (command.startsWith("M98")) {
    _m98();
  } else {
    Serial.println("Unknown command: " + command);
  }
}