#pragma once

#include "JoystickControlledActivator.h"

class ReverseActivator : public JoystickControlledActivator {
  private:
    int threshold;

  public:
    ReverseActivator(int joystickPin, int activatePin, int threshold);
    ReverseActivator(int joystickPin, int activatePin, int threshold, bool active);
    void update();
};
