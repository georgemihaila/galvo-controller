#include "SerialGCodeParser.h"

void SerialGCodeParser::_g1(char axis, int target) {
  if (axis == 'X') {
    _galvo->setXY(target, _galvo->getY());
  } else if (axis == 'Y') {
    _galvo->setXY(_galvo->getX(), target);
  }
}