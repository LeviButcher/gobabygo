#include "DistanceBuzzerControl.h"
#include "Arduino.h"

DistanceBuzzerControl::DistanceBuzzerControl(int buzzerPin, int intermittentDistance, int constantDistance) {
  this -> buzzerPin = buzzerPin;
  this -> intermittentDistance = intermittentDistance;
  this -> constantDistance = constantDistance;
  pinMode(buzzerPin, OUTPUT);
}

//TODO: refactor vehicle update to use DistanceBuzzer and change getState to be passed distances.

void DistanceBuzzerControl::update(int distance){
  //transitions
  switch(DB_STATE){
    case START:
      DB_STATE = OFF;
      break;
    case INTERMITTENT:
      if(distance < constantDistance) {
        DB_STATE = CONSTANT;
      }
      else if(distance > intermittentDistance) {
        DB_STATE = OFF;
      }
      break;
    case CONSTANT:
      if(distance > constantDistance && distance < intermittentDistance) {
        DB_STATE = INTERMITTENT;
      }
      else if(distance > intermittentDistance) {
        DB_STATE = OFF;
      }
      break;
    case OFF:
      if(distance < intermittentDistance && distance > constantDistance) {
        DB_STATE = INTERMITTENT;
      }
      else if(distance < constantDistance) {
        DB_STATE = CONSTANT;
      }
      break;
    default:
      DB_STATE = START;
  }

  //actions
  switch(DB_STATE){
    case START:
      digitalWrite(buzzerPin, false);
      break;
    case INTERMITTENT:
      static bool lastState = false;
      digitalWrite(buzzerPin, lastState);
      lastState = !lastState;
      break;
    case CONSTANT:
      digitalWrite(buzzerPin, true);
      break;
    case OFF:
      digitalWrite(buzzerPin, false);
      break;
    default:
      digitalWrite(buzzerPin, false);
  }
}
