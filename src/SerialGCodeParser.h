#pragma once
#include "XY2_100.h"
#include <Arduino.h>

class SerialGCodeParser {
private:
  XY2_100 *_galvo;
  int _baudRate;
  void _parse(String command);
#pragma region GCode implementation

  /// @brief  (Linear Move) The G1 command allows for all axes to move
  /// synchronously in a contoured linear motion. The parameters supplied will
  /// cause a motion in either a relative or absolute fashion depending on the
  /// G90 / G91 mode.
  /// @example G1 Z1.2 ;
  /// Move the Z axis 1.2 in. in the positive direction
  /// @param axis The axis to move
  /// @param value The distance to move
  void _g1(char axis, int value);
  void _g2();
  void _g3();
  void _g4();
  void _g9();
  void _g17();
  void _g18();
  void _g19();
  void _g90();
  void _g91();
  void _g92();
  void _m00();
  void _m01();
  void _m09();
  void _m13();
  void _m16();
  void _m17();
  void _m29();
  void _m30();
  void _m38();
  void _m39();
  void _m40();
  void _m41();
  void _m52();
  void _m53();
  void _m54();
  void _m56();
  void _m57();
  void _m60();
  void _m61();
  void _m98();

#pragma endregion

public:
  SerialGCodeParser(int baudRate, XY2_100 *galvo);

  /// @brief Listens for GCode commands on the serial port. In case nothing is
  /// sent, the connected XY2-100 devices's clock will be ticked.
  void listen();
};