/*
  SubChild of ServoControl, this control will move the position of the Servo to the exact value of the joystick Pin. It will never move farther then the maxDegrees allowed from centerDegrees

  Written By: Levi Butcher, Sean Rickard
 */

#pragma once

#include "Arduino.h"
#include "ServoControl.h"

class AnalogServoControl : public ServoControl
{
  private:
    static const int HISTORY_LENGTH = 15;
    static const int MAX_JOYSTICK_VAL = 1023;
    static const int MIN_JOYSTICK_VAL = 0;
    int history [HISTORY_LENGTH] = {-1};
    int historyIndex = 0;
    int currentPosition = middleDegrees;
    void addToHistory(int position);
    int averageUserIntent();

  public:
    AnalogServoControl(int newMaxDegreesForTurn, int xPin);
    AnalogServoControl(int newMaxDegreesForTurn, int xPin, int centerDegrees);

    void update();
};
