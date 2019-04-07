#include "Rangefinder.h"
#include "Arduino.h"

Rangefinder::Rangefinder(int triggerPin, int echoPin) {
  this -> triggerPin = triggerPin;
  this -> echoPin = echoPin;
}

int Rangefinder::getDistance() {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(10);
  unsigned long pulseTime = pulseIn(echoPin, HIGH);
  int distance = pulseTime/58;
  return distance;
}
