# GoBabyGo

GoBabyGo is a effort to allow physically disabled children have power over their own movement with custom battery powered vehicles.

This repository contains libraries used for the gobabygo project at WVUP from an embedded system class.

Here are the libraries and their responsibilities.

## MovementControl

This contains the main classes used for controlling when a vehicle should go forward based on user input from a joystick. Also, a front sensor and back sensor is attached to detect any object within a software defined length to stop movement or warn the user with a buzzer.

The director class is VehicleMovementControl and it composes all the other classes together.

## ServoControl

This contains the classes that handles turning a servo based on the position of a joystick. It uses a abstract class to handle setting up basic properties and methods. 3 implementation of turning a joystick has been made from the abstract class.

- AnalogServoControl: that turns the servo to match the exact postion of the joystick.
- BinaryServoControl: that slowly turns the Servo to the left or right when passed a software defined value
- ModBinaryServoControl: that slowly turns the Servo to the left or right when passed a software defined value but slowly returns to center position when joystick is in the middle

## MP3PinPlayer

This contains code that was modified from an example to allow a selector switch to play songs uploaded to a SD card. It is just a arduino script not a library.

[Original Source](https://learn.sparkfun.com/tutorials/mp3-player-shield-hookup/example-sketch-mp3-trigger)

# Internal Libraries Dependencies

- Servo Control
  - Servo Library provided by Arduino
- VehicleMovementControl
  - RangeFinder
    - NewPing, Version 1.9.0 -> [Source](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)
- MP3PinPlayer
  - VS1053 for use with Sdfat, Version 1.3.0 -> [Source](https://www.arduinolibraries.info/libraries/vs1053-for-use-with-sd-fat)

# Installing and Using Libraries

1. clone or download this repo
1. Copy MovementControl and/or ServoControl into the libraries folder on your machine
  1. This will be at `/home/{user}/Arduino/libraries` on Linux
  1. This will be at `C\Users\{user}\Documents\Arduino\libraries` on Windows
1. Install Internal Libraries dependencies above
1. Then create a new Arduino ino script and do `#include<VehicleMovementControl.h>` or whatever other class you'd like to use
1. View the examples for how to use them correctly

### HOT TIP

If you're on Linux and our developing a library of your own. Make a symbolic link to your Arduino/libraries folder to make it easier to test/develop.

EX. Say your libary was under /home/{user}/Documents/Projects/SweetLibrary

RUN `ln -s /home/{user}/Documents/Projects/SweetLibrary /home/{user}/Arduino/libraries`

Now you won't have to constantly copy your project over to arduino/libraries to test since it will have your live changes automatically with the symbolic link
