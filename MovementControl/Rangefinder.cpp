#include "Rangefinder.h"
#include "Arduino.h"

Rangefinder::Rangefinder(int triggerPin, int echoPin) {
  this -> triggerPin = triggerPin;
  this -> echoPin = echoPin;
  pinMode(this -> triggerPin, OUTPUT);
  pinMode(this -> echoPin, INPUT);
}

int Rangefinder::getDistance() {
  int distance = this -> calcDistance();
  this -> addToHistory(distance);
  return this -> lowestDistance();
}

int Rangefinder::calcDistance() {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(10);
  unsigned long pulseTime = pulseIn(echoPin, HIGH);
  int distance = pulseTime/58;
  return distance;
}

void Rangefinder::addToHistory(int distanceValue) {
  static int position = 0;
  history[position] = distanceValue;
  position = (position + 1) % historyLength;
}

// Precondition: history has at least one element
int Rangefinder::lowestDistance() {
  int smallest = history[0];
  for(int i = 1; i < historyLength; i++) {
    smallest = smallest < history[i] ? smallest : history[i];
  }
  return smallest;
}
