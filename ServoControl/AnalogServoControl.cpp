/*
  SubChild of ServoControl, this control will move the position of the Servo to the exact value of the joystick Pin. It will never move farther then the maxDegrees allowed from centerDegrees

  Written By: Levi Butcher, Sean Rickard
 */

 #include "Arduino.h"
 #include "ServoControl.h"
 #include "AnalogServoControl.h"
 #include "Smoother.h"

 AnalogServoControl::AnalogServoControl(int newMaxDegreesForTurn, int xPin) : ServoControl(newMaxDegreesForTurn, xPin) {

 }

 AnalogServoControl::AnalogServoControl(int newMaxDegreesForTurn, int xPin, int centerDegrees) : ServoControl(newMaxDegreesForTurn, xPin, centerDegrees) {
   this -> history = new Smoother(HISTORY_LENGTH);
 }

 void AnalogServoControl::update() {
  int xPosition = getJoystickPosition();
  history -> addToHistory(xPosition);
  int average = history -> averageHistory();
  int pos = map(average, MIN_JOYSTICK_VAL, MAX_JOYSTICK_VAL, middleDegrees - maxDegreesForTurn, middleDegrees +
    maxDegreesForTurn);
  pos = constrain(pos, middleDegrees - maxDegreesForTurn, middleDegrees + maxDegreesForTurn);

  // make right left and left right
  if(pos > middleDegrees) {
    int difference = pos - middleDegrees;
    pos = middleDegrees - difference;
  }
  else if(pos < middleDegrees) {
    int difference = middleDegrees - pos;
    pos = middleDegrees + difference;
  }


  if(currentPosition != pos) {
    steeringServo.write(pos);
    currentPosition = pos;
  }
 }
