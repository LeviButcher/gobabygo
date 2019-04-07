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
