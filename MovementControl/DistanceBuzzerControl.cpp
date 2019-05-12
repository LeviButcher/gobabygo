/*
  DistanceBuzzerControl

  DistanceBuzzerControl will either constantly buzz a buzzer, intermittenly buzz a buzzer, or not buzz a buzzer depending on internal state

  Pass in a distance to start intermittent Buzzing and a distance for constant buzzing and pass
  a distance from a object, then the update method will handle the states for you

  Written By: Levi Butcher
 */

#include "DistanceBuzzerControl.h"
#include "Arduino.h"
#include <Wire.h>
#include <MedianFilter.h>

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
      if(distance < intermittentDistance && distance > constantDistance && distance != 0) {
        DB_STATE = INTERMITTENT;
      }
      else if(distance < constantDistance && distance != 0) {
        DB_STATE = CONSTANT;
      }
      break;
    default:
      DB_STATE = START;
  }

  //actions
  switch(DB_STATE){
    case START:
      digitalWrite(buzzerPin, true);
      break;
    case INTERMITTENT:
      static bool lastState = false;
      digitalWrite(buzzerPin, lastState);
      lastState = !lastState;
      break;
    case CONSTANT:
      digitalWrite(buzzerPin, false);
      break;
    case OFF:
      digitalWrite(buzzerPin, true);
      break;
    default:
      digitalWrite(buzzerPin, true);
  }
}

bool DistanceBuzzerControl::isConstantBuzz() {
  return DB_STATE == CONSTANT;
}
