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