#include "VehicleMovementController.h"
#include "Arduino.h"

VehicleMovementController::VehicleMovementController(int joystickYPin, int forwardThreshold, int reverseThreshold, int forwardRelayPin, int reverseRelayPin, int frontRangefinderTriggerPin, int  frontRangefinderEchoPin, int backRangefinderTriggerPin, int backRangefinderEchoPin, int antiPlugDelay, int buzzerPin, int buzzerDistance, int stopDistance) {

  forwardJoystickRelay = new JoystickControlledActivator(joystickYPin, forwardRelayPin);
  reverseJoystickRelay = new JoystickControlledActivator(joystickYPin, reverseRelayPin);
  rearRangefinder = new Rangefinder(frontRangefinderTriggerPin, frontRangefinderEchoPin);
  frontRangefinder = new Rangefinder(backRangefinderTriggerPin, backRangefinderEchoPin);
  this -> antiPlugDelay = antiPlugDelay;
  this -> buzzerPin = buzzerPin;
  this -> buzzerDistance = buzzerDistance;
  this -> stopDistance = stopDistance;
  this -> forwardThreshold = forwardThreshold;
  this -> reverseThreshold = reverseThreshold;
}


void VehicleMovementController::update(int currentMilli) {
  int frontDistance = frontRangefinder -> getDistance();
  int backDistance = rearRangefinder -> getDistance();

  if(frontDistance <= stopDistance || backDistance <= stopDistance) {
    forwardJoystickRelay -> deactivate();
    reverseJoystickRelay -> deactivate();
    this -> buzzOn();
  }
  else if(frontDistance <= buzzerDistance || backDistance <= buzzerDistance) {
    this -> buzzToggle();
  }
  else {
      if(plugging) {
        if(currentMilli - engagedPluggingTime > antiPlugDelay) {
          plugging = false;
          engagedPluggingTime = 0;
        }
      }
      else {
        this -> buzzOff();
        int currJoystickY = forwardJoystickRelay -> getJoystickPosition();
        if(currJoystickY >= forwardThreshold) {
          if(reverseJoystickRelay -> isActivated()) {
            // Turn on pluging
            plugging = true;
            engagedPluggingTime = millis();
            reverseJoystickRelay -> deactivate();
            forwardJoystickRelay -> deactivate();
          }
          else {
            reverseJoystickRelay -> deactivate();
            forwardJoystickRelay -> activate();
          }
        }
        else if(currJoystickY <= reverseThreshold) {
          if(forwardJoystickRelay -> isActivated()) {
            // Turn on pluging
            plugging = true;
            engagedPluggingTime = millis();
            reverseJoystickRelay -> deactivate();
            forwardJoystickRelay -> deactivate();
          }
          else {
            forwardJoystickRelay -> deactivate();
            reverseJoystickRelay -> activate();
          }
        }
      }
  }
}

void VehicleMovementController::buzzOn() {
  digitalWrite(buzzerPin, HIGH);
}

void VehicleMovementController::buzzOff() {
  digitalWrite(buzzerPin, HIGH);
}

void VehicleMovementController::buzzToggle() {
  // have to add variable to keep track
  digitalWrite(buzzerPin, HIGH);
}
