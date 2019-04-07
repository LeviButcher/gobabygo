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

     if(xValue < leftTrigger && currentPosition > MID_DEGREES - maxDegreesForTurn) {
         currentPosition--;
         steeringServo.write(currentPosition);
     }
     else if(xValue > rightTrigger && currentPosition < MID_DEGREES + maxDegreesForTurn) {
         currentPosition++;
         steeringServo.write(currentPosition);
     }
     else {
         //Joystick is not within triggers, begin approaching center
         if(currentPosition < MID_DEGREES) {
             currentPosition++;
             steeringServo.write(currentPosition);
         }
         else if(currentPosition > MID_DEGREES) {
             currentPosition--;
             steeringServo.write(currentPosition);
         }
     }
     Serial.println(currentPosition);
 }
