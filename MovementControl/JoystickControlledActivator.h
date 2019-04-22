/*
  JoystickControlledActivator

  This class wil take a joystickPin to read from and a pin to activate and exposes methods to allow one to get the joystickPin value, activate the pin, deactivate the pin, and get if the pin is activate or not

  Written By: Levi Butcher, Sean Rickard
 */

#pragma once

#include "Arduino.h"

class JoystickControlledActivator {
  private:
    int joystickPin;
    int activatePin;
    bool active;


  public:
    JoystickControlledActivator(int joystickPin, int activatePin);
    JoystickControlledActivator(int joystickPin, int activatePin, bool active);
    void activate();
    void deactivate();
    bool isActivated();
    int getJoystickPosition();
};
