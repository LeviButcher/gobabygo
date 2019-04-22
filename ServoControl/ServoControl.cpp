/*
  Servo Control is a abstract parent class that allows a child of this class to use the values from a joystick Pin to control the movement of a servo attached to this class

  Written By: Levi Butcher, Sean Ricard
 */

#include "Arduino.h"
#include "ServoControl.h"
#include "Servo.h"

ServoControl::ServoControl(int newMaxDegreesForTurn, int xPin) : ServoControl::ServoControl(newMaxDegreesForTurn, xPin, 90) {
}

ServoControl::ServoControl(int newMaxDegreesForTurn, int xPin, int middleDegrees) {
  maxDegreesForTurn = newMaxDegreesForTurn;
  joystickXPin = xPin;
  this -> middleDegrees = middleDegrees;
}

void ServoControl::attach(int servoPin) {
  steeringServo.attach(servoPin);
  steeringServo.write(middleDegrees);
}

int ServoControl::getJoystickPosition() {
  return analogRead(joystickXPin);
}
