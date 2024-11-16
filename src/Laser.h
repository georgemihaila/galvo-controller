#pragma once

class Laser {
private:
  int _pin;
  double _power;
  unsigned int _pulseFrequency;
  double _dutyCycle;

public:
  /// @brief Construct a new Laser object
  /// @param pin The MCU's PWM pin used to control the laser
  /// @param power The laser's power in *Watts*
  /// @param pulseFrequency The laser's pulse frequency in *Hz*
  /// @param dutyCycle The laser's duty cycle as a *percentage* ([0, 1])
  Laser(int pin, double power, unsigned int pulseFrequency, double dutyCycle);
  void turnOn();
  void turnOff();
  void setPower(double power);
  void setPulseFrequency(unsigned int pulseFrequency);
  void setDutyCycle(double dutyCycle);
  double getPower();
  int getPulseFrequency();
  double getDutyCycle();
  double getPowerInJoulesPerSecond();
};