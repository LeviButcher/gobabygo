/*

 */

#ifndef AnalogServoControl_h
#define AnalogServoControl_h

#include "Arduino.h"
#include "ServoControl.h"

class AnalogServoControl : public ServoControl
{
  public:
    AnalogServoControl(int newMaxDegreesForTurn, int xPin);

    void update();
};
#endif
