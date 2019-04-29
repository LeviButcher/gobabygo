#include <VehicleMovementController.h>

const int JOYSTICK_Y_PIN = A1;
const int FORWARD_THRESHOLD = 900; // 0 - 1023
const int REVERSE_THRESHOLD = 300; // 0 - 1023
const int FORWARD_RELAY_PIN = 3;
const int REVERSE_RELAY_PIN = 4;
const int FRONT_RANGEFINDER_TRIGGER_PIN = 11;
const int FRONT_RANGEFINDER_ECHO_PIN = 10;
const int BACK_RANGEFINDER_TRIGGER_PIN = 13;
const int BACK_RANGEFINDER_ECHO_PIN = 12;
const int ANTI_PLUG_DELAY = 1000; // Milliseconds
const int BUZZER_PIN = 7;
const int BUZZER_DISTANCE = 60; // Inches
const int STOP_DISTANCE = 15; // Inches
const int TIME_TILL_VEHICLE_UPDATE = 100; // Milliseconds

VehicleMovementController* vehicle;
Rangefinder* rearRangefinder;
Rangefinder* frontRangefinder;
JoystickControlledActivator* forwardJoystickRelay;
JoystickControlledActivator* reverseJoystickRelay;
DistanceBuzzerControl* buzzerControl;



void setup() {
  frontRangefinder = new Rangefinder(FRONT_RANGEFINDER_TRIGGER_PIN, FRONT_RANGEFINDER_ECHO_PIN);
  rearRangefinder = new Rangefinder(BACK_RANGEFINDER_TRIGGER_PIN, BACK_RANGEFINDER_ECHO_PIN);
  forwardJoystickRelay = new JoystickControlledActivator(JOYSTICK_Y_PIN, FORWARD_RELAY_PIN);
  reverseJoystickRelay = new JoystickControlledActivator(JOYSTICK_Y_PIN, REVERSE_RELAY_PIN);
  buzzerControl = new DistanceBuzzerControl(BUZZER_PIN, BUZZER_DISTANCE, STOP_DISTANCE);

  vehicle = new VehicleMovementController(forwardJoystickRelay, reverseJoystickRelay, frontRangefinder, rearRangefinder, buzzerControl, FORWARD_THRESHOLD, REVERSE_THRESHOLD, ANTI_PLUG_DELAY, STOP_DISTANCE, TIME_TILL_VEHICLE_UPDATE);
  Serial.begin(9600);
}

void loop() {
  int mille = millis();
  vehicle -> update(mille);
  // Serial.println(vehicle -> getState());
}
