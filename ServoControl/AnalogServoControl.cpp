/*

 */

 #include "Arduino.h"
 #include "ServoControl.h"
 #include "AnalogServoControl.h"

 AnalogServoControl::AnalogServoControl(int newMaxDegreesForTurn, int xPin) : ServoControl(newMaxDegreesForTurn, xPin) {

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
  Serial.println(pos);
 }

void AnalogServoControl::addToHistory(int position) {
  history[historyIndex] = position;
  historyIndex = (historyIndex + 1) % HISTORY_LENGTH;
}

int AnalogServoControl::getJoystickPosition() {
  return analogRead(joystickXPin);
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
