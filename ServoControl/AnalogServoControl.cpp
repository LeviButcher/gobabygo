/*
  SubChild of ServoControl, this control will move the position of the Servo to the exact value of the joystick Pin. It will never move farther then the maxDegrees allowed from centerDegrees

  Written By: Levi Butcher, Sean Rickard
 */

 #include "Arduino.h"
 #include "ServoControl.h"
 #include "AnalogServoControl.h"

 AnalogServoControl::AnalogServoControl(int newMaxDegreesForTurn, int xPin) : ServoControl(newMaxDegreesForTurn, xPin) {

 }

 AnalogServoControl::AnalogServoControl(int newMaxDegreesForTurn, int xPin, int centerDegrees) : ServoControl(newMaxDegreesForTurn, xPin, centerDegrees) {

 }

 void AnalogServoControl::update() {
  int xPosition = getJoystickPosition();
  addToHistory(xPosition);
  int average = averageUserIntent();
  int pos = map(average, MIN_JOYSTICK_VAL, MAX_JOYSTICK_VAL, middleDegrees - maxDegreesForTurn, middleDegrees +
    maxDegreesForTurn);
  pos = constrain(pos, middleDegrees - maxDegreesForTurn, middleDegrees + maxDegreesForTurn);
  if(currentPosition != pos) {
    steeringServo.write(pos);
    currentPosition = pos;
  }
  Serial.println(xPosition);
 }

void AnalogServoControl::addToHistory(int position) {
  history[historyIndex] = position;
  historyIndex = (historyIndex + 1) % HISTORY_LENGTH;
}

int AnalogServoControl::averageUserIntent() {
  int total = 0;
  int count = 0;
  for(int i = 0; i < HISTORY_LENGTH; i++) {
    if(history[i] != -1) {
      total = total + history[i];
      count++;
    }
  }
  return total / count;
}
