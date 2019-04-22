/*
  Servo Control is a abstract parent class that allows a child of this class to use the values from a joystick Pin to control the movement of a servo attached to this class

  Written By: Levi Butcher, Sean Ricard
 */
#pragma once

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
      int getJoystickPosition();
      virtual void update() = 0;
};
