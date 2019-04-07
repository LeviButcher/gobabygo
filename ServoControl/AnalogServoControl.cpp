/*

 */

 #include "Arduino.h"
 #include "ServoControl.h"
 #include "AnalogServoControl.h"

 AnalogServoControl::AnalogServoControl(int newMaxDegreesForTurn, int xPin) : ServoControl(newMaxDegreesForTurn, xPin) {

 }

 void AnalogServoControl::update() {
   int xValue = analogRead(joystickXPin);
   int pos = map(xValue, 0, 1023, MID_DEGREES - maxDegreesForTurn, MID_DEGREES + maxDegreesForTurn);
   steeringServo.write(pos);
   Serial.println(pos);
 }
