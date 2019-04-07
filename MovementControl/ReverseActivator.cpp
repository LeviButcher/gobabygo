#include "ReverseActivator.h"

ReverseActivator::ReverseActivator(int joystickPin, int activatePin, int threshold) : ReverseActivator(joystickPin, activatePin, threshold, false){}


ReverseActivator::ReverseActivator(int joystickPin, int activatePin, int threshold, bool active) :  JoystickControlledActivator(joystickPin, activatePin, active) {
    this -> threshold = threshold;
}


void ReverseActivator::update() {
  if(getJoystickPosition() < threshold) {
    activate();
  }
  else {
    deactivate();
  }
}
