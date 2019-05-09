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
#include <Wire.h>
#include <MedianFilter.h>

#define VERY_LARGE_NUMBER 1000
#define MAX_DISTANCE 450 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

MedianFilter filter(31,0);

Rangefinder::Rangefinder(int triggerPin, int echoPin) {
  this -> triggerPin = triggerPin;
  this -> echoPin = echoPin;
  pinMode(this -> triggerPin, OUTPUT);
  pinMode(this -> echoPin, INPUT);
  this -> history = new Smoother(HISTORY_LENGTH);
  this -> sonar = new NewPing(triggerPin, echoPin, MAX_DISTANCE);
}

int Rangefinder::getDistance() {
  int distance = this -> calcDistance();
  history -> addToHistory(distance);
  return history -> averageHistory();
}

int Rangefinder::calcDistance() {
  unsigned int o,uS = sonar -> ping();
  filter.in(uS);
  o = filter.out();
  int distance = sonar -> convert_in(o);
  if(distance == 0) {
    distance = VERY_LARGE_NUMBER;
  }
  return distance;
}
