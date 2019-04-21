/*

 */

 #include "Arduino.h"
 #include "ServoControl.h"
 #include "ModBinaryServoControl.h"

 ModBinaryServoControl::ModBinaryServoControl(int newMaxDegreesForTurn, int xPin, int newLeftTrigger, int newRightTrigger) : ServoControl(newMaxDegreesForTurn, xPin) {
     leftTrigger = newLeftTrigger;
     rightTrigger = newRightTrigger;
 }

 void ModBinaryServoControl::update() {
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
         //Joystick is not within triggers, begin approaching center
         if(currentPosition < middleDegrees) {
             currentPosition++;
             steeringServo.write(currentPosition);
         }
         else if(currentPosition > middleDegrees) {
             currentPosition--;
             steeringServo.write(currentPosition);
         }
     }
     Serial.println(currentPosition);
 }
