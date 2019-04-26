/*
  Rangefinder

  Uses the NewPing library to retrieve the distance from a object
  from a sensor

  Written By: Levi Butcher, Sean Rickard
 */

#include "Rangefinder.h"
#include "Arduino.h"
#include "NewPing.h"
#include "Smoother.h"

#define VERY_LARGE_NUMBER 1000000

Rangefinder::Rangefinder(int triggerPin, int echoPin) {
  this -> triggerPin = triggerPin;
  this -> echoPin = echoPin;
  pinMode(this -> triggerPin, OUTPUT);
  pinMode(this -> echoPin, INPUT);
  this -> history = new Smoother(HISTORY_LENGTH);
  this -> sonar = new NewPing(triggerPin, echoPin, 500);
}

int Rangefinder::getDistance() {
  int distance = this -> calcDistance();
  history -> addToHistory(distance);
  return history -> averageHistory();
}

int Rangefinder::calcDistance() {
  int distance =  sonar -> ping_in();
  if(distance == 0) {
    distance = VERY_LARGE_NUMBER;
  }
  return distance;
}
