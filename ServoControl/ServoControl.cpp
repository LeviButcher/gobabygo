/*

 */

#include "Arduino.h"
#include "ServoControl.h"
#include "Servo.h"

ServoControl::ServoControl(int newMaxDegreesForTurn, int xPin) {
  maxDegreesForTurn = newMaxDegreesForTurn;
  joystickXPin = xPin;
}

void ServoControl::attach(int servoPin) {
  steeringServo.attach(servoPin);
  steeringServo.write(MID_DEGREES);
}
