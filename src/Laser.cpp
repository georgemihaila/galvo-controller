#include "Laser.h"
#include <Arduino.h>

Laser::Laser(int pin, double power, unsigned int pulseFrequency,
             double pulseWidth) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  setPower(power);
  setPulseFrequency(pulseFrequency);
  _pulseWidth = pulseWidth;
  turnOff();
}

void Laser::turnOn() { analogWrite(_pin, _pulseWidth); }

void Laser::turnOff() { analogWrite(_pin, 0); }

void Laser::setPower(double power) { _power = power; }

void Laser::setPulseFrequency(int pulseFrequency) {
  _pulseFrequency = pulseFrequency;
}

void Laser::setDutyCycle(double dutyCycle) {
  if (dutyCycle > 1) {
    dutyCycle = 1;
  } else if (dutyCycle < 0) {
    dutyCycle = 0;
  }
  _dutyCycle = dutyCycle;
}

double Laser::getPower() { return _power; }

unsigned int Laser::getPulseFrequency() { return _pulseFrequency; }

double Laser::getDutyCycle() { return _dutyCycle; }

double Laser::getPowerInJoulesPerSecond() {
  return _power * 0.001 * _dutyCycle;
}