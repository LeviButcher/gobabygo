#include <Rangefinder.h>
#include <DistanceBuzzerControl.h>

const int FRONT_RANGEFINDER_TRIGGER_PIN = 11;
const int FRONT_RANGEFINDER_ECHO_PIN = 10;
const int BUZZER_PIN = 7;
const int BUZZER_DISTANCE = 36; // Inches
const int STOP_DISTANCE = 12; // Inches


Rangefinder* frontRanger;
DistanceBuzzerControl* buzzerControl;

void setup() {
  frontRanger = new Rangefinder(FRONT_RANGEFINDER_TRIGGER_PIN, FRONT_RANGEFINDER_ECHO_PIN);
  buzzerControl = new DistanceBuzzerControl(BUZZER_PIN, BUZZER_DISTANCE, STOP_DISTANCE);
  Serial.begin(9600);
}

void loop() {
  int distance = frontRanger -> getDistance();
  Serial.println(distance);
  buzzerControl -> update(distance);
  delay(1000);
}
