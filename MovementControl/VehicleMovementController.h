/*
    VehicleMovementControl
    
    Activates 2 relays the contol forward and reverse circuits on a battery controlled vehicle.
    Also, hooked to 2 rangefinders that detect if a object is so close to the vehicle
    If so then the Vehicle will stop
    A delay is also configured to prevent going back and forth between forward and stop frequently

    Author: Levi Butcher, Sean Rickard, Bradley, Robert
 */
#pragma once

#include "JoystickControlledActivator.h"
#include "Rangefinder.h"
#include "DistanceBuzzerControl.h"

class VehicleMovementController {
  private:
    JoystickControlledActivator* forwardJoystickRelay;
    JoystickControlledActivator* reverseJoystickRelay;
    Rangefinder* rearRangefinder;
    Rangefinder* frontRangefinder;
    DistanceBuzzerControl* buzzerControl;
    int antiPlugDelay;
    int forwardThreshold;
    int reverseThreshold;
    int stopDistance;
    int engagedPluggingTime = 0;
    int timeTillUpdate;
    enum VM_STATES {START, STOPPED, FORWARD, REVERSE, START_ANTI_PLUGGING, ANTI_PLUGGING};
    enum JOYSTICK_STATES {JOY_HIGH, JOY_LOW, JOY_MID};
    enum DETECTED_OBJECT_STATES {FRONT, BACK, CLEAR};
    VM_STATES VM_STATE;

    void engageForward();
    void engageReverse();
    enum JOYSTICK_STATES getJoystickState();
    enum DETECTED_OBJECT_STATES getDetectedObjectState(int frontDistance, int backDistance);


  public:
    VehicleMovementController(JoystickControlledActivator* forwardRelay, JoystickControlledActivator* reverseRelay, Rangefinder* frontRangefinder, Rangefinder* rearRangefinder, DistanceBuzzerControl* buzzerControl, int forwardThreshold, int reverseThreshold, int antiPlugDelay, int stopDistance, int timeTillUpdate);

    void update(int currentMilli);
    void stopVehicle();
    String getState();

};
