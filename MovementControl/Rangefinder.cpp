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
  return sonar -> ping_in();
}
