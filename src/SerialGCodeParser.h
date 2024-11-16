#pragma once
#include "XY2_100.h"
#include <Arduino.h>

class SerialGCodeParser {
private:
  XY2_100 *_galvo;
  int _baudRate;
  void _parse(String command);
#pragma region GCode definition
  /**
   * @brief Executes a G1 Linear Move command.
   *
   * The G1 command allows for all axes to move synchronously in a contoured
   * linear motion. The parameters supplied will cause a motion in either a
   * relative or absolute fashion depending on the G90/G91 mode.
   *
   * Example:
   * G1 Z1.2 ; Move the Z axis 1.2 units in the positive direction
   *
   * @param axis The axis to move (e.g., 'X', 'Y', 'Z').
   * @param value The distance to move along the specified axis.
   */
  void _g1(char axis, int value);

  /**
   * @brief Executes a G2 Circular Move command (Clockwise Rotation).
   *
   * The G2 command is used for making circular or elliptical type motion
   * profiles. It generates a clockwise rotation and can be determined using the
   * right-hand rule from the negative direction of an orthogonal axis.
   *
   * Example:
   * G2 X2 Y-2 I1.5 J-1.5 ; End Point and circle center specified (IJK method)
   * G2 X2 Y-2 R1.58114 ; End Point and radius specified
   */
  void _g2();

  /**
   * @brief Executes a G3 Circular Move command (Counter-Clockwise Rotation).
   *
   * The G3 command is used for making circular or elliptical type motion
   * profiles. It generates a counter-clockwise rotation and can be determined
   * using the right-hand rule from the negative direction of an orthogonal
   * axis.
   *
   * Example:
   * G3 X2 Y-2 I1.5 J-1.5 ; End Point and circle center specified (IJK method)
   * G3 X2 Y-2 R1.58114 ; End Point and radius specified
   */
  void _g3();

  /**
   * @brief Executes a G4 Dwell command.
   *
   * The G4 command causes a delay in program execution. The parameter supplied
   * by the user is in seconds and has a maximum resolution of 0.001 seconds.
   *
   * Example:
   * G4 P0.2 ; Dwell for 0.2 seconds
   *
   * @param seconds The duration to dwell in seconds.
   */
  void _g4();
  /**
   * @brief G9 Exact Stop
   *
   * The G9 command stops the program from continuing its run until all drives
   * have finished their instructed travel.
   *
   * Example:
   * @code
   * G1 X4.8 Y2.4
   * G9
   * @endcode
   */
  void _g9();
  /**
   * @brief Executes a G17 Plane Select command (XY Plane).
   *
   * The G17 command selects the XY plane for circular motion commands (G2 and
   * G3).
   */
  void _g17();

  /**
   * @brief Executes a G18 Plane Select command (ZX Plane).
   *
   * The G18 command selects the ZX plane for circular motion commands (G2 and
   * G3).
   */
  void _g18();

  /**
   * @brief Executes a G19 Plane Select command (YZ Plane).
   *
   * The G19 command selects the YZ plane for circular motion commands (G2 and
   * G3).
   */
  void _g19();

  /**
   * @brief Executes a G90 Absolute Distance Mode command.
   *
   * The G90 command sets the machine to absolute distance mode, where all
   * coordinates are interpreted as absolute positions from the origin.
   *
   * Example:
   * G90
   * G01 X3.0 Y7.0
   * G01 X5.0 Y10.0
   * G01 X10.0 Y6.0
   * ; These commands would generate the following move sequence:
   * ; (0,0) -> (3,7) -> (5,10) -> (10,6)
   */
  void _g90();

  /**
   * @brief Executes a G91 Incremental Distance Mode command.
   *
   * The G91 command sets the machine to incremental distance mode, where all
   * coordinates are interpreted as relative positions from the current
   * position.
   *
   * Example:
   * G91
   * G01 X3.0 Y7.0
   * G01 X5.0 Y10.0
   * G01 X10.0 Y6.0
   * ; These commands would generate the following move sequence:
   * ; (0,0) -> (3,7) -> (8,17) -> (18,23)
   */
  void _g91();

  /**
   * @brief Executes a G92 Redefine Coordinate System Set command.
   *
   * The G92 command sets the current position to the specified coordinates,
   * allowing the user to redefine the origin for absolute coordinates.
   *
   * Example:
   * G1 X5 Y5 ; Move to (5,5)
   * G92 X-1.0 Y-1.0 ; Set (6,6) as Home
   * G1 X0 Y0 ; Move to (6,6)
   */
  void _g92();

  /**
   * @brief Executes an M00 Stop command.
   *
   * The M00 command stops the program execution, allowing the operator to jog
   * or otherwise alter the system. Pressing the "Cycle Start" button will
   * resume the program sequence.
   */
  void _m00();

  /**
   * @brief Executes an M01 Optional Stop command.
   *
   * The M01 command pauses the program execution if the optional stop checkbox
   * is checked. A popup message dialog will display, allowing the operator to
   * jog or otherwise alter the system. Pressing the "OK" button will close the
   * popup and resume the program sequence.
   *
   * Example:
   * M01 S1 ; Select message 1 to display in M01 popup message dialog
   */
  void _m01();

  /**
   * @brief Executes an M09 Status Message Display command.
   *
   * The M09 command displays a programmable custom status message on the Status
   * Message Display window, with options for custom background color and
   * flashing.
   *
   * Example:
   * M09 S1 F1 C1
   * S1 = Load and display Custom Status Message 1
   * F1 = Enable flashing of status message
   * C1 = CloudBlue
   */
  void _m09();

  /**
   * @brief Executes an M13 Set QCW Laser Firing Parameters command.
   *
   * The M13 command sets the peak power, pulse frequency, and pulse width of
   * the laser.
   *
   * Example:
   * M13 P45 F10 W100
   */
  void _m13();

  /**
   * @brief Executes an M16 Gas On command.
   *
   * The M16 command turns on the gas.
   */
  void _m16();

  /**
   * @brief Executes an M17 Gas Off command.
   *
   * The M17 command turns off the gas.
   */
  void _m17();

  /**
   * @brief Executes an M29 Tube Diameter Input command.
   *
   * The M29 command allows the operator to change the value of the tube
   * diameter of the part.
   *
   * Example:
   * M29 S1 D0.28
   */
  void _m29();

  /**
   * @brief Executes an M30 Stop Program Execution command.
   *
   * The M30 command stops the program execution.
   */
  void _m30();

  /**
   * @brief Executes an M38 Water On command.
   *
   * The M38 command turns on the water.
   */
  void _m38();

  /**
   * @brief Executes an M39 Water Off command.
   *
   * The M39 command turns off the water.
   */
  void _m39();

  /**
   * @brief Executes an M40 Collet Open command.
   *
   * The M40 command opens the collet.
   */
  void _m40();

  /**
   * @brief Executes an M41 Collet Close command.
   *
   * The M41 command closes the collet.
   */
  void _m41();

  /**
   * @brief Executes an M52 Laser Pendant Mode command (External Mode Off).
   *
   * The M52 command puts the laser into Pendant Mode for Laser 1 or Laser 2.
   *
   * Example:
   * M52 L1 ; Put Laser 1 to Pendant Mode
   * M52 L2 ; Put Laser 2 to Pendant Mode
   */
  void _m52();

  /**
   * @brief Executes an M53 Laser External Mode command (Laser Reference Only).
   *
   * The M53 command puts the laser into External Mode for Welder 1 or Welder 2.
   *
   * Example:
   * M53 L1 ; Put Welder 1 to External Mode
   * M53 L2 ; Put Laser 2 to External Mode
   */
  void _m53();

  /**
   * @brief Executes an M54 Laser On command.
   *
   * The M54 command turns on the laser.
   */
  void _m54();

  /**
   * @brief Executes an M56 Guide Beam On command.
   *
   * The M56 command turns on the Guide Beam on Laser 1 or Laser 2.
   *
   * Example:
   * M56 L1 ; Turn Guide Beam On for Laser 1
   * M56 L2 ; Turn Guide Beam On for Laser 2
   */
  void _m56();

  /**
   * @brief Executes an M57 Guide Beam Off command.
   *
   * The M57 command turns off the Guide Beam on Laser 1 or Laser 2.
   *
   * Example:
   * M57 L1 ; Turn Guide Beam Off for Laser 1
   * M57 L2 ; Turn Guide Beam Off for Laser 2
   */
  void _m57();

  /**
   * @brief Executes an M60 Branch Shutter 1 Open command.
   *
   * The M60 command opens the Branch Shutter 1 of Laser 1 or Laser 2.
   *
   * Example:
   * M60 L1 ; Open Branch Shutter 1 On for Laser 1
   * M60 L2 ; Open Branch Shutter 1 On for Laser 2
   */
  void _m60();

  /**
   * @brief Executes an M61 Branch Shutter 1 Close command.
   *
   * The M61 command closes the Branch Shutter 1 of Laser 1 or Laser 2.
   *
   * Example:
   * M61 L1 ; Close Branch Shutter 1 On for Laser 1
   * M61 L2 ; Close Branch Shutter 1 On for Laser 2
   */
  void _m61();

  /**
   * @brief Executes an M98 Universal Wait for M-var to become equal to a
   * specified value command.
   *
   * The M98 command waits for a specified M-variable to become equal to a
   * specified value.
   */
  void _m98();

#pragma endregion

public:
  SerialGCodeParser(int baudRate, XY2_100 *galvo);

  /// @brief Listens for GCode commands on the serial port. In case nothing is
  /// sent, the connected XY2-100 devices's clock will be ticked.
  void listen();
};