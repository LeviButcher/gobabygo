#pragma once

class Rangefinder {
  private:
    int triggerPin;
    int echoPin;

  public:
    Rangefinder(int triggerPin, int echoPin);
    int getDistance();
};
