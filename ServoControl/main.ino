const int JOYSTICK_X_PIN = A0;
const int SERVO_PIN = 9;
const int MAX_DEGREES = 40;

ModBinaryServoControl myNewServo(MAX_DEGREES, JOYSTICK_X_PIN, 300, 800);

void setup() {
  myNewServo.attach(SERVO_PIN);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
}

void loop() {
    myNewServo.update();
}
