const int JOYSTICK_X_PIN = A0;
const int SERVO_PIN = 9;
const int MAX_DEGREES = 40;

#include <AnalogServoControl.h>
#include <BinaryServoControl.h>
#include <ModBinaryServoControl.h>
#include <Servo.h>

AnalogServoControl myNewServo(MAX_DEGREES, JOYSTICK_X_PIN);
// BinaryServoControl myNewServo(MAX_DEGREES, JOYSTICK_X_PIN, 300, 800);
// ModBinaryServoControl myNewServo(MAX_DEGREES, JOYSTICK_X_PIN, 300, 800);

void setup() {
  myNewServo.attach(SERVO_PIN);
  Serial.begin(9600);
}

bool firstTime = true;

void loop() {
    myNewServo.update();
    delay(100);
}
