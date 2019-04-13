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
    int engagedPluggingTime = 0;
    enum VM_STATES {START, STOPPED, FORWARD, REVERSE, START_ANTI_PLUGGING, ANTI_PLUGGING,LOCK_FORWARD,LOCK_REVERSE,LOCK_BOTH};
    enum JOYSTICK_STATES {JOY_HIGH, JOY_LOW, JOY_MID};
    enum DETECTED_OBJECT_STATES {FRONTSTOP, BACKSTOP, BOTHSTOP, CLEAR};
    VM_STATES VM_STATE;

    void engageForward();
    void engageReverse();
    enum JOYSTICK_STATES getJoystickState();
    enum DETECTED_OBJECT_STATES getDetectedObjectState();


  public:
    VehicleMovementController(JoystickControlledActivator* forwardRelay, JoystickControlledActivator* reverseRelay, Rangefinder* frontRangefinder, Rangefinder* rearRangefinder, int forwardThreshold, int reverseThreshold, int antiPlugDelay, int buzzerPin, int buzzerDistance, int stopDistance);

    void update(int currentMilli);
    void stopVehicle();
    String getState();

};
