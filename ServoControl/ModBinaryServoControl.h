/*

*/

#ifndef ModBinaryServoControl_h
#define ModBinaryServoControl_h

#include "Arduino.h"
#include "ServoControl.h"

class ModBinaryServoControl : public ServoControl
{
  private:
   int leftTrigger;
   int rightTrigger;
   int currentPosition = middleDegrees;
  public:
    ModBinaryServoControl(int newMaxDegreesForTurn, int xPin, int newLeftTrigger, int newRightTrigger);

    void update();
};
#endif
