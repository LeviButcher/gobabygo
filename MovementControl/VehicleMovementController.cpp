#include "VehicleMovementController.h"
#include "Arduino.h"

VehicleMovementController::VehicleMovementController(int joystickYPin, int forwardThreshold, int reverseThreshold, int forwardRelayPin, int reverseRelayPin, int frontRangefinderTriggerPin, int  frontRangefinderEchoPin, int backRangefinderTriggerPin, int backRangefinderEchoPin, int antiPlugDelay, int buzzerPin, int buzzerDistance, int stopDistance) {

  forwardJoystickRelay = new JoystickControlledActivator(joystickYPin, forwardRelayPin);
  reverseJoystickRelay = new JoystickControlledActivator(joystickYPin, reverseRelayPin);
  frontRangefinder = new Rangefinder(frontRangefinderTriggerPin, frontRangefinderEchoPin);
  rearRangefinder = new Rangefinder(backRangefinderTriggerPin, backRangefinderEchoPin);
  this -> antiPlugDelay = antiPlugDelay;
  this -> buzzerPin = buzzerPin;
  this -> buzzerDistance = buzzerDistance;
  this -> stopDistance = stopDistance;
  this -> forwardThreshold = forwardThreshold;
  this -> reverseThreshold = reverseThreshold;
}

// TODO: CHANGE JOYSTICK STATE INTO METHODS
void VehicleMovementController::update(int currentMilli) {
  //gather variables
  int frontDistance = frontRangefinder -> getDistance();
  int backDistance = rearRangefinder -> getDistance();
  int joystickYPos = forwardJoystickRelay -> getJoystickPosition();
  //Transitions
  switch(this -> VM_STATE) {
    case START:
      VM_STATE = STOPPED;
      break;
    case STOPPED:
      if(joystickYPos >= forwardThreshold && frontDistance > stopDistance) {
        VM_STATE = FORWARD;
      }
      else if(joystickYPos < reverseThreshold && backDistance > stopDistance) {
        VM_STATE = REVERSE;
      }
      else if(frontDistance <= stopDistance && backDistance > stopDistance) {
        VM_STATE = LOCK_FORWARD;
      }
      else if(backDistance <= stopDistance && frontDistance > stopDistance) {
        VM_STATE = LOCK_REVERSE;
      }
      else if(backDistance <= stopDistance && frontDistance <= stopDistance) {
        VM_STATE = LOCK_BOTH;
      }
      break;
    case FORWARD:
      if(joystickYPos < reverseThreshold) {
        VM_STATE = START_ANTI_PLUGGING;
      }
      else if((joystickYPos < forwardThreshold && joystickYPos > reverseThreshold) || frontDistance <= stopDistance) {
        VM_STATE = STOPPED;
      }
      break;
    case REVERSE:
      if(joystickYPos > forwardThreshold) {
        VM_STATE = START_ANTI_PLUGGING;
      }
      else if((joystickYPos < forwardThreshold && joystickYPos > reverseThreshold) || backDistance <= stopDistance) {
        VM_STATE = STOPPED;
      }
      break;
    case START_ANTI_PLUGGING:
      VM_STATE = ANTI_PLUGGING;
      break;
    case ANTI_PLUGGING:
      if(joystickYPos < reverseThreshold && currentMilli - engagedPluggingTime > antiPlugDelay && backDistance >= stopDistance) {
        VM_STATE = REVERSE;
      }
      else if(joystickYPos > forwardThreshold && currentMilli - engagedPluggingTime > antiPlugDelay && frontDistance >= stopDistance) {
        VM_STATE = FORWARD;
      }
      break;
    case LOCK_FORWARD:
      if(joystickYPos < reverseThreshold && backDistance > stopDistance) {
        VM_STATE = REVERSE;
      }
      else if(backDistance <= stopDistance && frontDistance <= stopDistance) {
        VM_STATE = LOCK_BOTH;
      }
      else if(joystickYPos > reverseThreshold && joystickYPos < forwardThreshold) {
        VM_STATE = STOPPED;
      }
      break;
    case LOCK_REVERSE:
      if(joystickYPos > forwardThreshold && frontDistance > stopDistance) {
        VM_STATE = REVERSE;
      }
      else if(backDistance <= stopDistance && frontDistance <= stopDistance) {
        VM_STATE = LOCK_BOTH;
      }
      else if(joystickYPos > reverseThreshold && joystickYPos < forwardThreshold) {
        VM_STATE = STOPPED;
      }
      break;
    case LOCK_BOTH:
      if(backDistance > stopDistance && frontDistance > stopDistance) {
        VM_STATE = STOPPED;
      }
      if(frontDistance <= stopDistance && backDistance > stopDistance) {
        VM_STATE = LOCK_FORWARD;
      }
      if(backDistance <= stopDistance && frontDistance > stopDistance) {
        VM_STATE = LOCK_REVERSE;
      }
      break;
    default:
      this -> VM_STATE = START;
  }
  //Actions
  switch(this -> VM_STATE) {
    case START:
      break;
    case STOPPED:
      stopVehicle();
      break;
    case FORWARD:
      engageForward();
      break;
    case REVERSE:
      engageReverse();
      break;
    case START_ANTI_PLUGGING:
      engagedPluggingTime = currentMilli;
      break;
    case ANTI_PLUGGING:
      stopVehicle();
      break;
    case LOCK_FORWARD:
      //constant buzz
      break;
    case LOCK_REVERSE:
      break;
    case LOCK_BOTH:
      break;
    default:
      stopVehicle();
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

void VehicleMovementController::stopVehicle(){
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
