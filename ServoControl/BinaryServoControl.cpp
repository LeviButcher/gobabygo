/*

 */

 #include "Arduino.h"
 #include "ServoControl.h"
 #include "BinaryServoControl.h"

 BinaryServoControl::BinaryServoControl(int newMaxDegreesForTurn, int xPin, int newLeftTrigger, int newRightTrigger) : ServoControl(newMaxDegreesForTurn, xPin) {
     leftTrigger = newLeftTrigger;
     rightTrigger = newRightTrigger;
 }

 void BinaryServoControl::update() {
     int xValue = analogRead(joystickXPin);

     if(xValue < leftTrigger && currentPosition > middleDegrees - maxDegreesForTurn) {
         currentPosition--;
         steeringServo.write(currentPosition);
     }
     else if(xValue > rightTrigger && currentPosition < middleDegrees + maxDegreesForTurn) {
         currentPosition++;
         steeringServo.write(currentPosition);
     }
     else {
         //Do Nothing
     }
     Serial.println(currentPosition);
 }
