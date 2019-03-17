// Read X and Y from joystick
// Output X and Y Digital Value on LCD Row 1
// Output X and Y Binary Value on LCD Row 2


// Look at README for direction for installation
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int xPin = A0;
const int yPin = A1;
//Connects to Bt pin on Joystick Module
const int togglePin = 12;
const int joystickPwrPin = 13;
const int time = 500;
bool binaryMode = false;
// Connect pin A4 to SDA on lcd
// Connect pin A5 to SCL on lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(joystickPwrPin, OUTPUT);
  pinMode(togglePin, INPUT);
  digitalWrite(joystickPwrPin, HIGH);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  String xOutput;
  String yOutput;
  // Joysticks button pin always true until pressed
  bool joystickPress = !digitalRead(togglePin);
  if(joystickPress) {
    binaryMode = !binaryMode;
  }
  if(binaryMode) {
    //convert to binary
    xOutput = intToBinaryString(xValue);
    yOutput = intToBinaryString(yValue);
  }
  else {
    xOutput = String(xValue);
    yOutput = String(yValue);
  }

  printToLCD(xOutput, yOutput);
  delay(1000);
}

void serialPrint(int x, int y) {
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("y: ");
  Serial.println(y);
}

void printToLCD(String x, String y){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("x: ");
  lcd.setCursor(3,0);
  lcd.print(x);
  lcd.setCursor(0,1);
  lcd.print("y: ");
  lcd.setCursor(3, 1);
  lcd.print(y);
}

// Precondition: Value is less then 1024
// // TODO: Need to refactor with a pointer for a char array passed in.
String intToBinaryString(int value) {
    int bitValue;
    String binary = "0000000000";
    if(value > 1024) {
      return binary;
    }
    // 10 bits to loop through
    for(int bitPos = 9; bitPos >= 0; bitPos--) {
      bitValue = value >> bitPos;
      if(bitValue & 1) {
        binary[bitPos] = '1';
      } else {
        binary[bitPos] = '0';
      }
    }
    return binary;
}
