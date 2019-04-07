#pragma once

#include "JoystickControlledActivator.h"

class ForwardActivator : public JoystickControlledActivator {
  private:
    int threshold;

  public:
    ForwardActivator(int joystickPin, int activatePin, int threshold);
    ForwardActivator(int joystickPin, int activatePin, int threshold, bool active);
    void update();
};
