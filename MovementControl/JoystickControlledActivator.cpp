#include "Arduino.h"
#include "JoystickControlledActivator.h"


JoystickControlledActivator::JoystickControlledActivator(int joystickPin, int activatePin) : JoystickControlledActivator(joystickPin, activatePin, false) {
}

JoystickControlledActivator::JoystickControlledActivator(int joystickPin, int activatePin, bool active) {
  this -> joystickPin = joystickPin;
  this -> activatePin = activatePin;
  pinMode(this -> activatePin, OUTPUT);
  digitalWrite(this -> activatePin, active);
  this -> active = active;
}

void JoystickControlledActivator::activate() {
  digitalWrite(this -> activatePin, HIGH);
  this -> active = true;
}

void JoystickControlledActivator::deactivate() {
  digitalWrite(this -> activatePin, LOW);
  this -> active = false;
}

bool JoystickControlledActivator::isActivated() {
  return this -> active;
}

int JoystickControlledActivator::getJoystickPosition() {
  return analogRead(this -> joystickPin);
}
