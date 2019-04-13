#include <Rangefinder.h>

const int FRONT_RANGEFINDER_TRIGGER_PIN = 10;
const int FRONT_RANGEFINDER_ECHO_PIN = 11;

Rangefinder* frontRanger;

void setup() {
  frontRanger = new Rangefinder(FRONT_RANGEFINDER_TRIGGER_PIN, FRONT_RANGEFINDER_ECHO_PIN);
  Serial.begin(9600);
}

void loop() {
  Serial.println(frontRanger -> getDistance());
  delay(11);
}
