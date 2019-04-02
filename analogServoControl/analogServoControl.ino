// Initialize servo position to 0 
// and read X value from joystick and convert 
// to a format agreeable with the servo
// and then position servo according to that value

// TODO: Restrict turning to not go past threshold

#include <Servo.h>

const int xPin = A0;
const int joystickPwrPin = 13;
int pos = 0;
int servoDelay = 25;
const int MAX_DEGREES_FOR_TURN = 40;
const int MID_DEGREES = 90;

Servo myservo;

void setup() {
  pinMode(joystickPwrPin, OUTPUT);
  digitalWrite(joystickPwrPin, HIGH);
  myservo.attach(9);
  myservo.write(pos);
  Serial.begin(9600);
  delay(25);
}

void loop() {
    int xValue = analogRead(xPin);
    pos = map(xValue, 0, 1023, MID_DEGREES - MAX_DEGREES_FOR_TURN, MID_DEGREES + MAX_DEGREES_FOR_TURN);
    myservo.write(pos);
    Serial.println(pos);
    delay(servoDelay);
}
