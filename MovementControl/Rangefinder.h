/*
  Rangefinder

  Uses the NewPing library to retrieve the distance from a object
  from a sensor

  Written By: Levi Butcher, Sean Rickard
 */

#pragma once

#include "NewPing.h"

class Rangefinder {
  private:
    int triggerPin;
    int echoPin;
    NewPing* sonar;
    static const int historyLength = 5;
    int history [historyLength];
    int calcDistance();
    void addToHistory(int distance);
    int lowestDistance();
  public:
    Rangefinder(int triggerPin, int echoPin);
    int getDistance();
};
