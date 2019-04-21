/*

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
    int getJoystickPosition();
    int averageUserIntent();

  public:
    AnalogServoControl(int newMaxDegreesForTurn, int xPin);


    void update();
};
