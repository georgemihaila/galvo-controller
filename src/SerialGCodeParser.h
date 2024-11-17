#pragma once
#include "Laser.h"
#include "XY2_100.h"
#include "defs.h"
#include <Arduino.h>

/// @brief Acts as a middleman between serial port inputs, anm XY2-100 galvo and
/// one or two lasers. This implementation is based on the LW600A Laser Welder's
/// GCode and MCode commands but shoule be compatibel with most implementations.
class SerialGCodeParser {
public:
  SerialGCodeParser(int baudRate, XY2_100 *galvo, Laser *laser1);
  SerialGCodeParser(int baudRate, XY2_100 *galvo, Laser *laser1, Laser *laser2);

  /// @brief Listens for GCode commands on the serial port. In case nothing is
  /// sent, the connected XY2-100 devices's clock will be ticked.
  void listen();

#pragma region GRBL

#pragma region States

  enum State {
    Alarm,
    Idle,
    Jog,
    Homing,
    Check,
    Cycle,
    Hold,
    SafetyDoor,
    Sleep
  };

  State _state = State::Idle;

#pragma endregion

#pragma region Errors

  enum ErrorCode {
    CommandLetterNotFound = 1,
    CommandValueInvalidOrMissing = 2,
    DollarSignNotSupported = 3,
    NegativeValueForExpectedPositiveValue = 4,
    HomingNotEnabled = 5,
    MinStepPulseMustBeGreaterThan3Microseconds = 6,
    EEPROMReadFailUsingDefault = 7,
    DollarSignOnlyValidWhenIdle = 8,
    GCodeNotAllowedWhileInAlarmOrJogState = 9,
    SoftLimitsRequireHoming = 10,
    MaxCharactersPerLineExceeded = 11,
    DollarSettingExceedsMaxStepRate = 12,
    SafetyDoorOpened = 13,
    BuildInfoOrStartupLineTooLong = 14,
    JogTargetExceedsMachineTravel = 15,
    JogCmdMissingOrProhibitedGCode = 16,
    LaserModeRequiresPWMOutput = 17,
    UnsupportedOrInvalidGCodeCommand = 20,
    MultipleGCodeCommandsInModalGroup = 21,
    FeedRateNotSetOrUndefined = 22,
    GCodeCommandRequiresIntegerValue = 23,
    MultipleGCodeCommandsUsingAxisWords = 24,
    RepeatedGCodeWordInBlock = 25,
    NoAxisWordsInCommandBlock = 26,
    LineNumberValueInvalid = 27,
    GCodeCmdMissingRequiredValueWord = 28,
    G59xWCSNotSupported = 29,
    G53OnlyValidWithG0AndG1 = 30,
    UnneededAxisWordsInBlock = 31,
    G2G3ArcsNeedInPlaneAxisWord = 32,
    MotionCommandTargetInvalid = 33,
    ArcRadiusValueInvalid = 34,
    G2G3ArcsNeedInPlaneOffsetWord = 35,
    UnusedValueWordsInBlock = 36,
    G431OffsetNotAssignedToToolLengthAxis = 37,
    ToolNumberGreaterThanMaxValue = 38
  };

  enum AlarmCode {
    HardLimitTriggered = 1,
    SoftLimitAlarm = 2,
    ResetWhileInMotion = 3,
    ProbeFailInitialState = 4,
    ProbeFailNoContact = 5,
    HomingFailCycleReset = 6,
    HomingFailDoorOpened = 7,
    HomingFailPullOffFailed = 8,
    HomingFailLimitSwitchNotFound = 9
  };

#pragma endregion

#pragma endregion
private:
  XY2_100 *_galvo;
  Laser *_laser1;
  Laser *_laser2;
  int _baudRate;
  bool _stopped;

#pragma region Plane select
#define XY 0
#define ZX 1
#define YZ 2
  byte _currentPlane = XY;
#pragma endregion

#pragma region Operation mode
  bool _absoluteMode = true;
  int _x_origin = 0;
  int _y_origin = 0;
#pragma endregion

  void _parse(String command);
#pragma region G / M Code definition

  /// @brief Executes a simultaneous XY fast move command. During this move, the
  /// laser is turned off.
  void _g0(int x, int y);

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
  void _g2(double x, double y, double i, double j, double r);

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
  void _g3(double x, double y, double i, double j, double r);

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
  void _g4(double seconds);

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
  void _g9(int targetX, int targetY);
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
  void _g92(int newXRelative, int newYRelative);

  /// @brief Executes a G28 Home command.
  void _g28();

  /// @brief Executes a G28.1 set home command using absolute coordinates.
  void _g28p1(int x, int y);

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

  /// @brief Resumes the program execution.
  void _m02();

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
  void _m09(String message, bool flash, String color);

  /**
   * @brief Executes an M13 Set QCW Laser Firing Parameters command.
   *
   * The M13 command sets the peak power, pulse frequency, and pulse width of
   * the laser.
   *
   * Example:
   * M13 P45 F10 W100
   */
  void _m13(int peakPower, int pulseFrequency, int pulseWidth);

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
  void _m29(double diameter);

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
  void _m52(String laser);

  /**
   * @brief Executes an M53 Laser External Mode command (Laser Reference Only).
   *
   * The M53 command puts the laser into External Mode for Welder 1 or Welder 2.
   *
   * Example:
   * M53 L1 ; Put Welder 1 to External Mode
   * M53 L2 ; Put Laser 2 to External Mode
   */
  void _m53(String laser);

  /**
   * @brief Executes an M54 Laser On command.
   *
   * The M54 command turns on the laser.
   */
  void _m54();

  /**
   * @brief Executes an M54 Laser Off command.
   *
   * The M55 command turns off the laser.
   */
  void _m55();

  /**
   * @brief Executes an M56 Guide Beam On command.
   *
   * The M56 command turns on the Guide Beam on Laser 1 or Laser 2.
   *
   * Example:
   * M56 L1 ; Turn Guide Beam On for Laser 1
   * M56 L2 ; Turn Guide Beam On for Laser 2
   */
  void _m56(String laser);

  /**
   * @brief Executes an M57 Guide Beam Off command.
   *
   * The M57 command turns off the Guide Beam on Laser 1 or Laser 2.
   *
   * Example:
   * M57 L1 ; Turn Guide Beam Off for Laser 1
   * M57 L2 ; Turn Guide Beam Off for Laser 2
   */
  void _m57(String laser);

  /**
   * @brief Executes an M60 Branch Shutter 1 Open command.
   *
   * The M60 command opens the Branch Shutter 1 of Laser 1 or Laser 2.
   *
   * Example:
   * M60 L1 ; Open Branch Shutter 1 On for Laser 1
   * M60 L2 ; Open Branch Shutter 1 On for Laser 2
   */
  void _m60(String laser);

  /**
   * @brief Executes an M61 Branch Shutter 1 Close command.
   *
   * The M61 command closes the Branch Shutter 1 of Laser 1 or Laser 2.
   *
   * Example:
   * M61 L1 ; Close Branch Shutter 1 On for Laser 1
   * M61 L2 ; Close Branch Shutter 1 On for Laser 2
   */
  void _m61(String laser);

  /**
   * @brief Executes an M98 Universal Wait for M-var to become equal to a
   * specified value command.
   *
   * The M98 command waits for a specified M-variable to become equal to a
   * specified value.
   */
  void _m98();

#pragma endregion

#pragma region G / M Code helpers
  void _set_guide_beam(String laser, bool state);
  void _set_branch_shutter(String laser, bool state);
  void _set_water(bool state);
  void _set_collet(bool state);
  void _set_gas(bool state);
  void _stop();
  void _resume();
  void _drawCircle(double x, double y, double i, double j, double r,
                   bool clockwise);
#pragma endregion

  bool _parseGCode(String gcodeString);
  bool _parseMCode(String mcodeString);
  bool _parseGRBL(String commandString);

#pragma region GRBL
#pragma region Errors

  String _errorToString(ErrorCode code);

  void _printError(ErrorCode code);
#pragma endregion
#pragma region Alarms

  String _alarmToString(AlarmCode code);

  void _printAlarm(AlarmCode code);
#pragma endregion
#pragma region Non G - code commands

  /**
   * @brief Display Grbl Settings.
   */
  void displaySettings();

  /**
   * @brief Change Grbl Setting x to val.
   * @param x The setting number.
   * @param val The value to set.
   */
  void changeSetting(int x, double val);

  /**
   * @brief View GCode Parameters.
   */
  void viewGCodeParameters();

  /**
   * @brief View GCode parser state.
   */
  void viewGCodeParserState();

  /**
   * @brief Toggle Check Gcode Mode.
   */
  void toggleCheckGCodeMode();

  /**
   * @brief Run Homing Cycle.
   */
  void runHomingCycle();

  /**
   * @brief Run Jogging Motion.
   * @param gcode The jogging GCode command.
   */
  void runJoggingMotion(String gcode);

  /**
   * @brief Kill Alarm Lock state.
   */
  void killAlarmLock();

  /**
   * @brief View Build Info.
   */
  void viewBuildInfo();

  /**
   * @brief View saved start up code.
   */
  void viewSavedStartUpCode();

  /**
   * @brief Save Start-up GCode line.
   * @param x The line number (0 or 1).
   * @param line The GCode line to save.
   */
  void saveStartUpGCodeLine(int x, String line);

  /**
   * @brief Restores the Grbl settings to defaults.
   */
  void restoreSettingsToDefaults();

  /**
   * @brief Erases G54-G59 WCS offsets and G28/30 positions stored in EEPROM.
   */
  void eraseWCSOffsets();

  /**
   * @brief Clear and Load all data from EEPROM.
   */
  void clearAndLoadEEPROM();

  /**
   * @brief Enable Sleep mode.
   */
  void enableSleepMode();

  /**
   * @brief Soft Reset.
   */
  void softReset();

  /**
   * @brief Status report query.
   */
  void statusReportQuery();

  /**
   * @brief Cycle Start/Resume from Feed Hold, Door or Program pause.
   */
  void cycleStartResume();

  /**
   * @brief Feed Hold – Stop all motion.
   */
  void feedHold();

#pragma endregion
#pragma endregion
};