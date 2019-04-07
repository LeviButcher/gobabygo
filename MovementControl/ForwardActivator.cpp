#include "ForwardActivator.h"

ForwardActivator::ForwardActivator(int joystickPin, int activatePin, int threshold) : ForwardActivator(joystickPin, activatePin, threshold, false) {

}

ForwardActivator::ForwardActivator(int joystickPin, int activatePin, int threshold, bool active) :  JoystickControlledActivator(joystickPin, activatePin, active) {
    this -> threshold = threshold;
}


void ForwardActivator::update() {
  if(getJoystickPosition() > threshold) {
    activate();
  }
  else {
    deactivate();
  }
}
