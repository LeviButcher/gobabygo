// Read X and Y from joystick
// Output X and Y Digital Value on LCD Row 1
// Output X and Y Binary Value on LCD Row 2


// Look at README for direction for installation
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int xPin = A0;
const int yPin = A1;
const int joystickPwrPin = 13;
const int time = 500;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(joystickPwrPin, OUTPUT);
  digitalWrite(joystickPwrPin, HIGH);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  serialPrint(xValue, yValue);
  printToLCD(xValue, yValue);
  delay(2000);
}

void serialPrint(int x, int y) {
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("y: ");
  Serial.println(y);
}

void printToLCD(int x, int y){
  char binX[] = intToBinaryString(x);
  char binY[] = intToBinaryString(y);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("x: ");
  lcd.setCursor(3,0);
  lcd.print(x);
  lcd.setCursor(8,0);
  lcd.print("y: ");
  lcd.setCursor(10, 0);
  lcd.print(y);
}

// Precondition: Value is less then 1024
// TODO: Need to refactor with a pointer for a char array passed in.
char* intToBinaryString(int value) {
    int bitValue;
    char binary[10];
    if(value > 1024) {
      return binary;
    }
    // 10 bits to loop through
    for(int bitPos = 9; bitPos >= 0; bitPos--) {
      bitValue = value >> bitPos;
      binary[bitPos] = bitValue & 1;
    }
    return binary;
}
