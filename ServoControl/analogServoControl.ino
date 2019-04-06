// Initialize servo position to 0 
// and read X value from joystick and convert 
// to a format agreeable with the servo
// and then position servo according to that value

// TODO: Restrict turning to not go past threshold



class AnalogServoControl : public ServoControl
{
  public:
    AnalogServoControl(int newMaxDegreesForTurn, int xPin) : ServoControl(newMaxDegreesForTurn, xPin) {
        
    }
    
    update() {
      int xValue = analogRead(joystickXPin);
      int pos = map(xValue, 0, 1023, MID_DEGREES - maxDegreesForTurn, MID_DEGREES + maxDegreesForTurn);
      steeringServo.write(pos);
      Serial.println(pos);
    }
};
