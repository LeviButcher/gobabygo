#pragma once

#include "JoystickControlledActivator.h"
#include "Rangefinder.h"

class VehicleMovementController {
  private:
    JoystickControlledActivator* forwardJoystickRelay;
    JoystickControlledActivator* reverseJoystickRelay;
    Rangefinder* rearRangefinder;
    Rangefinder* frontRangefinder;
    int antiPlugDelay;
    int buzzerPin;
    int forwardThreshold;
    int reverseThreshold;
    int buzzerDistance;
    int stopDistance;
    int plugging = false;
    int engagedPluggingTime = 0;

    void engageForward();
    void engageReverse();
    void deactivateMovement();


  public:
    VehicleMovementController(int joystickYPin, int forwardThreshold, int reverseThreshold, int forwardRelayPin, int reverseRelayPin, int frontRangefinderTriggerPin, int  frontRangefinderEchoPin, int backRangefinderTriggerPin, int backRangefinderEchoPin, int antiPlugDelay, int buzzerPin, int buzzerDistance, int stopDistance);
    void update(int currentMilli);
    void buzzToggle();
    void buzzOn();
    void buzzOff();
    
};
