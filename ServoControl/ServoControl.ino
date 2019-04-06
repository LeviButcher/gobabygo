#include <Servo.h>

class ServoControl {
    protected:
      int maxDegreesForTurn;
      Servo steeringServo;
      int joystickXPin;
      const int MID_DEGREES = 90;

    public:
      ServoControl(int newMaxDegreesForTurn, int xPin) {
        maxDegreesForTurn = newMaxDegreesForTurn;
        joystickXPin = xPin;
      }

      attach(int servoPin) {
        steeringServo.attach(servoPin);
        steeringServo.write(MID_DEGREES);
      }

      virtual update() = 0;
};