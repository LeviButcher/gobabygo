#include "VehicleMovementController.h"
#include "Arduino.h"
#include <string.h>

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

void VehicleMovementController::update(int currentMilli) {
  //gather variables
  JOYSTICK_STATES joystickState = getJoystickState();
  DETECTED_OBJECT_STATES detectedObjectState = getDetectedObjectState();

  //Transitions
  switch(this -> VM_STATE) {
    case START:
      VM_STATE = STOPPED;
      break;
    case STOPPED:
      if(joystickState == JOY_HIGH && (detectedObjectState != FRONTSTOP && detectedObjectState != BOTHSTOP)) {
        VM_STATE = FORWARD;
      }
      else if(joystickState == JOY_LOW && (detectedObjectState != BACKSTOP && detectedObjectState!= BOTHSTOP)) {
        VM_STATE = REVERSE;
      }
      else if(detectedObjectState == FRONTSTOP) {
        VM_STATE = LOCK_FORWARD;
      }
      else if(detectedObjectState == BACKSTOP) {
        VM_STATE = LOCK_REVERSE;
      }
      else if(detectedObjectState == BOTHSTOP) {
        VM_STATE = LOCK_BOTH;
      }
      break;
    case FORWARD:
      if(joystickState == JOY_LOW) {
        VM_STATE = START_ANTI_PLUGGING;
      }
      else if(joystickState == JOY_MID || (detectedObjectState == FRONTSTOP || detectedObjectState == BOTHSTOP)) {
        VM_STATE = STOPPED;
      }
      break;
    case REVERSE:
      if(joystickState == JOY_HIGH) {
        VM_STATE = START_ANTI_PLUGGING;
      }
      else if(joystickState == JOY_MID || (detectedObjectState == BACKSTOP || detectedObjectState == BOTHSTOP)) {
        VM_STATE = STOPPED;
      }
      break;
    case START_ANTI_PLUGGING:
      VM_STATE = ANTI_PLUGGING;
      break;
    case ANTI_PLUGGING:
      if(joystickState == JOY_LOW && currentMilli - engagedPluggingTime > antiPlugDelay && detectedObjectState != BACKSTOP && detectedObjectState != BOTHSTOP) {
        VM_STATE = REVERSE;
      }
      else if(joystickState == JOY_HIGH && currentMilli - engagedPluggingTime > antiPlugDelay && detectedObjectState != FRONTSTOP && detectedObjectState != BOTHSTOP) {
        VM_STATE = FORWARD;
      }
      break;
    case LOCK_FORWARD:
      if(joystickState == JOY_LOW && (detectedObjectState != BACKSTOP && detectedObjectState != BOTHSTOP)) {
        VM_STATE = REVERSE;
      }
      else if(detectedObjectState == BOTHSTOP) {
        VM_STATE = LOCK_BOTH;
      }
      else if(joystickState == JOY_MID) {
        VM_STATE = STOPPED;
      }
      break;
    case LOCK_REVERSE:
      if(joystickState == JOY_HIGH && (detectedObjectState != FRONTSTOP && detectedObjectState != BOTHSTOP)) {
        VM_STATE = FORWARD;
      }
      else if(detectedObjectState == BOTHSTOP) {
        VM_STATE = LOCK_BOTH;
      }
      else if(joystickState == JOY_MID) {
        VM_STATE = STOPPED;
      }
      break;
    case LOCK_BOTH:
      if(detectedObjectState == CLEAR) {
        VM_STATE = STOPPED;
      }
      if(detectedObjectState == FRONTSTOP) {
        VM_STATE = LOCK_FORWARD;
      }
      if(detectedObjectState == BACKSTOP) {
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
      break;
    case LOCK_REVERSE:
      break;
    case LOCK_BOTH:
      break;
    default:
      stopVehicle();
  }
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

enum VehicleMovementController::DETECTED_OBJECT_STATES VehicleMovementController::getDetectedObjectState(){
  int frontDistance = frontRangefinder -> getDistance();
  int backDistance = rearRangefinder -> getDistance();

  if(frontDistance <= stopDistance && backDistance <= stopDistance) {
    return BOTHSTOP;
  }
  else if(frontDistance <= stopDistance) {
    return FRONTSTOP;
  }
  else if(backDistance <= stopDistance) {
    return BACKSTOP;
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
    case LOCK_FORWARD:
      return "LOCK_FORWARD";
    case LOCK_REVERSE:
      return "LOCK_REVERSE";
    case LOCK_BOTH:
      return "LOCK_BOTH";
    default:
      return "default";
  }
}
