/*
    VehicleMovementControl

    Activates 2 relays the contol forward and reverse circuits on a battery controlled vehicle.
    Also, hooked to 2 rangefinders that detect if a object is so close to the vehicle
    If so then the Vehicle will stop
    A delay is also configured to prevent going back and forth between forward and stop frequently

    Author: Levi Butcher, Sean Rickard, Bradley, Robert
 */
#include "VehicleMovementController.h"
#include "Arduino.h"

VehicleMovementController::VehicleMovementController(JoystickControlledActivator* forwardRelay, JoystickControlledActivator* reverseRelay, Rangefinder* frontRangefinder, Rangefinder* rearRangefinder, DistanceBuzzerControl* buzzerControl, int forwardThreshold, int reverseThreshold, int antiPlugDelay, int stopDistance, int timeTillUpdate){
  this -> forwardJoystickRelay = forwardRelay;
  this -> reverseJoystickRelay = reverseRelay;
  this -> frontRangefinder = frontRangefinder;
  this -> rearRangefinder = rearRangefinder;
  this -> buzzerControl = buzzerControl;
  this -> antiPlugDelay = antiPlugDelay;
  this -> stopDistance = stopDistance;
  this -> forwardThreshold = forwardThreshold;
  this -> reverseThreshold = reverseThreshold;
  this -> timeTillUpdate = timeTillUpdate;
}

void VehicleMovementController::update(int currentMilli) {
  static int timeSinceLastUpdate = 0;
  // VehicleMovement should only update after timeTillUpdate has passed
  if(timeSinceLastUpdate + timeTillUpdate > currentMilli) {
    return;
  }
  timeSinceLastUpdate = currentMilli;
  // gather variables
  int frontDistance = frontRangefinder -> getDistance();
  int backDistance = rearRangefinder -> getDistance();
  int lowestDistance = frontDistance <= backDistance ? frontDistance : backDistance;
  JOYSTICK_STATES joystickState = getJoystickState();
  DETECTED_OBJECT_STATES detectedObjectState = getDetectedObjectState(frontDistance, backDistance);

  // Transitions
  switch(this -> VM_STATE) {
    case START:
      VM_STATE = STOPPED;
      break;
    case STOPPED:
      if(joystickState == JOY_HIGH && detectedObjectState != FRONT) {
        VM_STATE = FORWARD;
      }
      else if(joystickState == JOY_LOW && detectedObjectState != BACK) {
        VM_STATE = REVERSE;
      }
      break;
    case FORWARD:
      if(joystickState == JOY_LOW) {
        VM_STATE = START_ANTI_PLUGGING;
      }
      else if(joystickState == JOY_MID || detectedObjectState == FRONT) {
        VM_STATE = STOPPED;
      }
      break;
    case REVERSE:
      if(joystickState == JOY_HIGH) {
        VM_STATE = START_ANTI_PLUGGING;
      }
      else if(joystickState == JOY_MID || detectedObjectState == BACK) {
        VM_STATE = STOPPED;
      }
      break;
    case START_ANTI_PLUGGING:
      VM_STATE = ANTI_PLUGGING;
      break;
    case ANTI_PLUGGING:
      if(joystickState == JOY_LOW && currentMilli - engagedPluggingTime > antiPlugDelay && detectedObjectState != BACK) {
        VM_STATE = REVERSE;
      }
      else if(joystickState == JOY_HIGH && currentMilli - engagedPluggingTime > antiPlugDelay && detectedObjectState != FRONT) {
        VM_STATE = FORWARD;
      }
      break;
    default:
      this -> VM_STATE = START;
  }
  // Actions
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
    default:
      stopVehicle();
  }

  // Update buzzerState last
  // BuzzerControl is it's own state machine controlling intermittent/constant buzzing depending on an objects distance
  Serial.println(lowestDistance);
  buzzerControl -> update(lowestDistance);
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

enum VehicleMovementController::JOYSTICK_STATES VehicleMovementController::getJoystickState() {
  int joystickYPos = forwardJoystickRelay -> getJoystickPosition();
  if(joystickYPos > forwardThreshold) {
    return JOY_HIGH;
  }
  else if(joystickYPos < reverseThreshold) {
    return JOY_LOW;
  }
  else {
    return JOY_MID;
  }
}

enum VehicleMovementController::DETECTED_OBJECT_STATES VehicleMovementController::getDetectedObjectState(int frontDistance, int backDistance){
  if(frontDistance <= stopDistance) {
    return FRONT;
  }
  else if(backDistance <= stopDistance) {
    return BACK;
  }
  else {
    return CLEAR;
  }
}

String VehicleMovementController::getState() {
  switch(VM_STATE){
    case START:
      return "START";
    case STOPPED:
      return "STOPPED";
    case FORWARD:
      return "FORWARD";
    case REVERSE:
      return "REVERSE";
    case START_ANTI_PLUGGING:
      return "START_ANTI_PLUGGING";
    case ANTI_PLUGGING:
      return "ANTI_PLUGGING";
    default:
      return "default";
  }
}
