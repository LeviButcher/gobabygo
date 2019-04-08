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
  static int idleTime = 0;

  // Stop car from going forward when object is within stopDistance
  if(frontDistance <= stopDistance) {
    forwardJoystickRelay -> deactivate();    
    this -> buzzOn();
  }
  // Stop car from going backward when object is within stopDistance
  else if( backDistance <= stopDistance) {
    reverseJoystickRelay -> deactivate();
    this -> buzzOn();
  }
  // Alert driver when object is in buzzerDistance
  else if(frontDistance <= buzzerDistance || backDistance <= buzzerDistance) {
    this -> buzzToggle();
  }
  // No Objects in stopDistance, we can move the car
  else {
      // Don't allow movement until enough time has passed that is greater then antiPlugDelay
      if(plugging) {
        if(currentMilli - engagedPluggingTime > antiPlugDelay) {
          plugging = false;
          engagedPluggingTime = 0;
        }
      }
      // Vehicle is not in plugging state, we can move
      else {
        this -> buzzOff();
        int currJoystickY = forwardJoystickRelay -> getJoystickPosition();
        // User wants to move forward
        if(currJoystickY >= forwardThreshold) {
          // Hack
          idleTime = 0;
          // User has went from reverse immediately to forward, engage plugging state
          if(reverseJoystickRelay -> isActivated()) {
            // Turn on pluging
            plugging = true;
            engagedPluggingTime = millis();
            this -> deactivateMovement();
          }
          // Engage forward Relay
          else {
            this -> engageForward();
          }
        }
        // User wants to move backward
        else if(currJoystickY <= reverseThreshold) {
          idleTime = 0;
          // User has went from forward immediately to reverse, engage plugging state
          if(forwardJoystickRelay -> isActivated()) {
            // Turn on pluging
            plugging = true;
            engagedPluggingTime = millis();
            this -> deactivateMovement();
          }
          // Engage reverse relay
          else {
            this -> engageReverse();
          }
        }
        else {
          // Hack to allow joystick in center to stop car, but only if the joystick has been in center for so long
          if(idleTime != 0) {
            if(currentMilli - idleTime > antiPlugDelay) {
              this -> deactivateMovement();
              idleTime = 0;
            }
          }
          // Record the starting time of being in center for the hack above
          else {
            idleTime = millis();
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

void VehicleMovementController::deactivateMovement(){
  reverseJoystickRelay -> deactivate();
  forwardJoystickRelay -> deactivate(); 
}

void VehicleMovementController::engageForward(){
  reverseJoystickRelay -> deactivate();
  forwardJoystickRelay -> activate(); 
}

void VehicleMovementController::engageReverse(){
  reverseJoystickRelay -> activate();
  forwardJoystickRelay -> deactivate(); 
}

