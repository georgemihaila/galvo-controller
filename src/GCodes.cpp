#include "SerialGCodeParser.h"

#define _galvo_mode_adjusted_x                                                 \
  (_galvo->getX() + (_absoluteMode ? _x_origin : 0))
#define _galvo_mode_adjusted_y                                                 \
  (_galvo->getY() + (_absoluteMode ? _y_origin : 0))

void SerialGCodeParser::_g1(char axis, int target) {
  if (axis == 'X') {
    _galvo->setXY(target, _galvo_mode_adjusted_y);
  } else if (axis == 'Y') {
    _galvo->setXY(_galvo_mode_adjusted_x, target);
  }
}

void SerialGCodeParser::_drawCircle(double x, double y, double i, double j,
                                    double r, bool clockwise) {
  int x0 = _galvo_mode_adjusted_x;
  int y0 = _galvo_mode_adjusted_y;

  double x1 = x0 + i;
  double y1 = y0 + j;

  double radius = r;
  if (r == 0) {
    // IJK method - i is the end point, j is the center
    radius = sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
  }

  if (clockwise) {
    _galvo->circleCW(x1, y1, radius, circle_n_points);
  } else {
    _galvo->circleCCW(x1, y1, radius, circle_n_points);
  }
}

void SerialGCodeParser::_g2(double x, double y, double i = 0, double j = 0,
                            double r = 0) {
  _drawCircle(x, y, i, j, r, true);
}

void SerialGCodeParser::_g3(double x, double y, double i = 0, double j = 0,
                            double r = 0) {
  _drawCircle(x, y, i, j, r, false);
}

void SerialGCodeParser::_g4(int seconds) { delay(seconds * 1000); }

void SerialGCodeParser::_g9(int x, int y) { _galvo->setXY(x, y); }

void SerialGCodeParser::_g17() { _currentPlane = XY; }

void SerialGCodeParser::_g18() { _currentPlane = ZX; }

void SerialGCodeParser::_g19() { _currentPlane = YZ; }

void SerialGCodeParser::_g90() { _absoluteMode = true; }

void SerialGCodeParser::_g91() { _absoluteMode = false; }

void SerialGCodeParser::_g92(int newXRelative, int newYRelative) {
  if (!_absoluteMode)
    return;
  int currentX = _galvo->getX();
  int currentY = _galvo->getY();
  _x_origin = currentX + newXRelative;
  _y_origin = currentY + newYRelative;
}

void SerialGCodeParser::_m13(int peakPower, int pulseFrequency,
                             int pulseWidth) {
  if (_laser1) {
    _laser1->setPower(peakPower);
    _laser1->setPulseFrequency(pulseFrequency);
    _laser1->setDutyCycle(pulseWidth);
  }
  if (_laser2) {
    _laser2->setPower(peakPower);
    _laser2->setPulseFrequency(pulseFrequency);
    _laser2->setDutyCycle(pulseWidth);
  }
}

void SerialGCodeParser::_m52(String laser) {
  Serial.println("M52 not supported");
}

void SerialGCodeParser::_m53(String laser) {
  Serial.println("M53 not supported");
}