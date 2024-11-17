#include "SerialGCodeParser.h"

String SerialGCodeParser::_errorToString(ErrorCode code) {
  switch (code) {
  case CommandLetterNotFound:
    return "GCode Command letter was not found.";
  case CommandValueInvalidOrMissing:
    return "GCode Command value invalid or missing.";
  case DollarSignNotSupported:
    return "Grbl '$' not recognized or supported.";
  case NegativeValueForExpectedPositiveValue:
    return "Negative value for an expected positive value.";
  case HomingNotEnabled:
    return "Homing fail. Homing not enabled in settings.";
  case MinStepPulseMustBeGreaterThan3Microseconds:
    return "Min step pulse must be greater than 3usec.";
  case EEPROMReadFailUsingDefault:
    return "EEPROM read failed. Default values used.";
  case DollarSignOnlyValidWhenIdle:
    return "Grbl '$' command only valid when Idle.";
  case GCodeNotAllowedWhileInAlarmOrJogState:
    return "GCode commands invalid in alarm or jog state.";
  case SoftLimitsRequireHoming:
    return "Soft limits require homing to be enabled.";
  case MaxCharactersPerLineExceeded:
    return "Max characters per line exceeded. Ignored.";
  case DollarSettingExceedsMaxStepRate:
    return "Grbl '$' setting exceeds the maximum step rate.";
  case SafetyDoorOpened:
    return "Safety door opened and door state initiated.";
  case BuildInfoOrStartupLineTooLong:
    return "Build info or start-up line > EEPROM line length.";
  case JogTargetExceedsMachineTravel:
    return "Jog target exceeds machine travel, ignored.";
  case JogCmdMissingOrProhibitedGCode:
    return "Jog Cmd missing '=' or has prohibited GCode.";
  case LaserModeRequiresPWMOutput:
    return "Laser mode requires PWM output.";
  case UnsupportedOrInvalidGCodeCommand:
    return "Unsupported or invalid GCode command.";
  case MultipleGCodeCommandsInModalGroup:
    return "More than one GCode command in a modal group in block.";
  case FeedRateNotSetOrUndefined:
    return "Feed rate has not yet been set or is undefined.";
  case GCodeCommandRequiresIntegerValue:
    return "GCode command requires an integer value.";
  case MultipleGCodeCommandsUsingAxisWords:
    return "More than one GCode command using axis words found.";
  case RepeatedGCodeWordInBlock:
    return "Repeated GCode word found in block.";
  case NoAxisWordsInCommandBlock:
    return "No axis words found in command block.";
  case LineNumberValueInvalid:
    return "Line number value is invalid.";
  case GCodeCmdMissingRequiredValueWord:
    return "GCode Cmd missing a required value word.";
  case G59xWCSNotSupported:
    return "G59.x WCS are not supported.";
  case G53OnlyValidWithG0AndG1:
    return "G53 only valid with G0 and G1 motion modes.";
  case UnneededAxisWordsInBlock:
    return "Unneeded axis words found in block.";
  case G2G3ArcsNeedInPlaneAxisWord:
    return "G2/G3 arcs need at least one in-plane axis word.";
  case MotionCommandTargetInvalid:
    return "Motion command target is invalid.";
  case ArcRadiusValueInvalid:
    return "Arc radius value is invalid.";
  case G2G3ArcsNeedInPlaneOffsetWord:
    return "G2/G3 arcs need at least one in-plane offset word.";
  case UnusedValueWordsInBlock:
    return "Unused value words found in block.";
  case G431OffsetNotAssignedToToolLengthAxis:
    return "G43.1 offset not assigned to tool length axis.";
  case ToolNumberGreaterThanMaxValue:
    return "Tool number greater than max value.";
  default:
    return "Unknown error code.";
  }
}

void SerialGCodeParser::_printError(ErrorCode code) {
  Serial.print("[E");
  Serial.print(code);
  Serial.print("] ");
  Serial.println(_errorToString(code));
}

String SerialGCodeParser::_alarmToString(AlarmCode code) {
  switch (code) {
  case HardLimitTriggered:
    return "Hard limit triggered. Position lost.";
  case SoftLimitAlarm:
    return "Soft limit alarm, position kept. Unlock is safe.";
  case ResetWhileInMotion:
    return "Reset while in motion. Position lost.";
  case ProbeFailInitialState:
    return "Probe fail. Probe not in expected initial state.";
  case ProbeFailNoContact:
    return "Probe fail. Probe did not contact the work.";
  case HomingFailCycleReset:
    return "Homing fail. The active homing cycle was reset.";
  case HomingFailDoorOpened:
    return "Homing fail. Door opened during homing cycle.";
  case HomingFailPullOffFailed:
    return "Homing fail. Pull off failed to clear limit switch.";
  case HomingFailLimitSwitchNotFound:
    return "Homing fail. Could not find limit switch.";
  default:
    return "Unknown alarm code.";
  }
}

void SerialGCodeParser::_printAlarm(AlarmCode code) {
  Serial.print("[A");
  Serial.print(code);
  Serial.print("] ");
  Serial.println(_alarmToString(code));
}

void SerialGCodeParser::displaySettings() {
  // Implementation to display Grbl settings
  Serial.println("Displaying Grbl settings...");
  // Add code to retrieve and display settings
}

void SerialGCodeParser::changeSetting(int x, double val) {
  // Implementation to change a specific Grbl setting
  Serial.print("Changing setting ");
  Serial.print(x);
  Serial.print(" to ");
  Serial.println(val);
  // Add code to change the setting
}

void SerialGCodeParser::viewGCodeParameters() {
  // Implementation to view GCode parameters
  Serial.println("Viewing GCode parameters...");
  // Add code to retrieve and display GCode parameters
}

void SerialGCodeParser::viewGCodeParserState() {
  // Implementation to view GCode parser state
  Serial.println("Viewing GCode parser state...");
  // Add code to retrieve and display GCode parser state
}

void SerialGCodeParser::toggleCheckGCodeMode() {
  // Implementation to toggle check GCode mode
  Serial.println("Toggling check GCode mode...");
  // Add code to toggle the mode
}

void SerialGCodeParser::runHomingCycle() {
  // Implementation to run homing cycle
  Serial.println("Running homing cycle...");
  // Add code to initiate homing cycle
}

void SerialGCodeParser::runJoggingMotion(String gcode) {
  // Implementation to run jogging motion
  Serial.print("Running jogging motion with GCode: ");
  Serial.println(gcode);
  // Add code to execute jogging motion
}

void SerialGCodeParser::killAlarmLock() {
  // Implementation to kill alarm lock state
  Serial.println("Killing alarm lock state...");
  // Add code to kill alarm lock
}

void SerialGCodeParser::viewBuildInfo() {
  // Implementation to view build info
  Serial.println("Viewing build info...");
  // Add code to retrieve and display build info
}

void SerialGCodeParser::viewSavedStartUpCode() {
  // Implementation to view saved start-up code
  Serial.println("Viewing saved start-up code...");
  // Add code to retrieve and display start-up code
}

void SerialGCodeParser::saveStartUpGCodeLine(int x, String line) {
  // Implementation to save start-up GCode line
  Serial.print("Saving start-up GCode line ");
  Serial.print(x);
  Serial.print(": ");
  Serial.println(line);
  // Add code to save the start-up GCode line
}

void SerialGCodeParser::restoreSettingsToDefaults() {
  // Implementation to restore settings to defaults
  Serial.println("Restoring settings to defaults...");
  // Add code to restore settings
}

void SerialGCodeParser::eraseWCSOffsets() {
  // Implementation to erase WCS offsets
  Serial.println("Erasing WCS offsets...");
  // Add code to erase WCS offsets
}

void SerialGCodeParser::clearAndLoadEEPROM() {
  // Implementation to clear and load all data from EEPROM
  Serial.println("Clearing and loading EEPROM...");
  // Add code to clear and load EEPROM
}

void SerialGCodeParser::enableSleepMode() {
  // Implementation to enable sleep mode
  Serial.println("Enabling sleep mode...");
  // Add code to enable sleep mode
}

void SerialGCodeParser::softReset() {
  // Implementation to perform a soft reset
  Serial.println("Performing soft reset...");
  // Add code to perform soft reset
}

void SerialGCodeParser::statusReportQuery() {
  // Implementation to query status report
  Serial.println("Querying status report...");
  // Add code to query status report
}

void SerialGCodeParser::cycleStartResume() {
  // Implementation to cycle start/resume
  Serial.println("Cycle start/resume...");
  // Add code to start or resume cycle
}

void SerialGCodeParser::feedHold() {
  // Implementation to feed hold (stop all motion)
  Serial.println("Feed hold - stopping all motion...");
  // Add code to stop all motion
}