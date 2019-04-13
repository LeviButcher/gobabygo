#include <VehicleMovementController.h>

const int JOYSTICK_Y_PIN = A1;
const int FORWARD_THRESHOLD = 900;
const int REVERSE_THRESHOLD = 300;
const int FORWARD_RELAY_PIN = 3;
const int REVERSE_RELAY_PIN = 4;
const int FRONT_RANGEFINDER_TRIGGER_PIN = 10;
const int FRONT_RANGEFINDER_ECHO_PIN = 11;
const int BACK_RANGEFINDER_TRIGGER_PIN = 12;
const int BACK_RANGEFINDER_ECHO_PIN = 13;
const int ANTI_PLUG_DELAY = 1000;
const int BUZZER_PIN = 7;
const int BUZZER_DISTANCE = 96;
const int STOP_DISTANCE = 48;

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

  vehicle = new VehicleMovementController(forwardJoystickRelay, reverseJoystickRelay, frontRangefinder, rearRangefinder, buzzerControl, FORWARD_THRESHOLD, REVERSE_THRESHOLD, ANTI_PLUG_DELAY, STOP_DISTANCE);
  Serial.begin(9600);
}

void loop() {
  int mille = millis();
  vehicle -> update(mille);
  Serial.println(vehicle -> getState());
  delay(100);
}
