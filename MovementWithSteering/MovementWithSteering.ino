#include "VehicleMovementController.h"
#include "AnalogServoControl.h"
#include "BinaryServoControl.h"
#include "ModBinaryServoControl.h"

const int JOYSTICK_Y_PIN = A1;
const int JOYSTICK_X_PIN = A0;
const int SERVO_PIN = 9;
const int MAX_DEGREES = 40;
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
const int BUZZER_DISTANCE = 36; // Inches
const int STOP_DISTANCE = 12; // Inches
const int TIME_TILL_VEHICLE_UPDATE = 100; // Milliseconds

VehicleMovementController* vehicle;
Rangefinder* rearRangefinder;
Rangefinder* frontRangefinder;
JoystickControlledActivator* forwardJoystickRelay;
JoystickControlledActivator* reverseJoystickRelay;
DistanceBuzzerControl* buzzerControl;
AnalogServoControl myNewServo(MAX_DEGREES, JOYSTICK_X_PIN);

void setup() {
  frontRangefinder = new Rangefinder(FRONT_RANGEFINDER_TRIGGER_PIN, FRONT_RANGEFINDER_ECHO_PIN);
  rearRangefinder = new Rangefinder(BACK_RANGEFINDER_TRIGGER_PIN, BACK_RANGEFINDER_ECHO_PIN);
  forwardJoystickRelay = new JoystickControlledActivator(JOYSTICK_Y_PIN, FORWARD_RELAY_PIN);
  reverseJoystickRelay = new JoystickControlledActivator(JOYSTICK_Y_PIN, REVERSE_RELAY_PIN);
  buzzerControl = new DistanceBuzzerControl(BUZZER_PIN, BUZZER_DISTANCE, STOP_DISTANCE);

  vehicle = new VehicleMovementController(forwardJoystickRelay, reverseJoystickRelay, frontRangefinder, rearRangefinder, buzzerControl, FORWARD_THRESHOLD, REVERSE_THRESHOLD, ANTI_PLUG_DELAY, STOP_DISTANCE, TIME_TILL_VEHICLE_UPDATE);
  myNewServo.attach(SERVO_PIN);
  Serial.begin(9600);

}

void loop() {
  int mille = millis();
  vehicle -> update(mille);
  myNewServo.update();
}
