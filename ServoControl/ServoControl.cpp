/*

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
