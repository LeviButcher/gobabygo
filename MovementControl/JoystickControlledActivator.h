#pragma once

#include "Arduino.h"

class JoystickControlledActivator {
  private:
    int joystickPin;
    int activatePin;

  protected:
    JoystickControlledActivator(int joystickPin, int activatePin);
    JoystickControlledActivator(int joystickPin, int activatePin, bool active);

  public:
    void activate();
    void deactivate();
    int getJoystickPosition();
    virtual void update() = 0;
};
