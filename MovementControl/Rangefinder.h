/*
  Rangefinder

  Uses the NewPing library to retrieve the distance from a object
  from a sensor

  Written By: Levi Butcher, Sean Rickard
 */

#pragma once

#include "NewPing.h"
#include "Smoother.h"

class Rangefinder {
  private:
    int triggerPin;
    int echoPin;
    NewPing* sonar;
    static const int HISTORY_LENGTH = 5;
    Smoother* history;
    int calcDistance();

  public:
    Rangefinder(int triggerPin, int echoPin);
    int getDistance();
};
