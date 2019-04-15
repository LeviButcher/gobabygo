#pragma once

class Rangefinder {
  private:
    int triggerPin;
    int echoPin;
    static const int historyLength = 5;
    int history [historyLength];
    int calcDistance();
    void addToHistory(int distance);
    int lowestDistance();
  public:
    Rangefinder(int triggerPin, int echoPin);
    int getDistance();
};
