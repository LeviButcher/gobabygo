#include <ForwardActivator.h>

const int JOYSTICK_Y_PIN = 9;
const int THRESHOLD = 600;
const int FORWARD_RELAY_PIN = 3;

ForwardActivator joystickControl(JOYSTICK_Y_PIN, FORWARD_RELAY_PIN, THRESHOLD);

void setup() {

}

void loop() {
  joystickControl.update();
}
