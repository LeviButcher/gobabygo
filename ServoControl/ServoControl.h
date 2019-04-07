/*

 */

#ifndef ServoControl_h
#define ServoControl_h

#include "Arduino.h"
#include "Servo.h"

class ServoControl {
    protected:
      int maxDegreesForTurn;
      Servo steeringServo;
      int joystickXPin;
      const int MID_DEGREES = 90;

    public:
      ServoControl(int newMaxDegreesForTurn, int xPin);

      void attach(int servoPin);

      virtual void update() = 0;
};
#endif
