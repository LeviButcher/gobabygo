/*

*/

#ifndef BinaryServoControl_h
#define BinaryServoControl_h

#include "Arduino.h"
#include "ServoControl.h"

class BinaryServoControl : public ServoControl
{
  private:
    int leftTrigger;
    int rightTrigger;
    int currentPosition = middleDegrees;

  public:
    BinaryServoControl(int newMaxDegreesForTurn, int xPin, int newLeftTrigger, int newRightTrigger);

    void update();
};
#endif
