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
      int middleDegrees = 90;

    public:
      ServoControl(int newMaxDegreesForTurn, int xPin);
      ServoControl(int newMaxDegreesForTurn, int xPin, int middleDegrees);

      void attach(int servoPin);

      virtual void update() = 0;
};
#endif
