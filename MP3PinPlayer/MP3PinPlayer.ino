                                                                                                                      /*
  MP3 Shield Trigger
  by: Jim Lindblom
      SparkFun Electronics
  date: September 23, 2013

  This is an example MP3 trigger sketch for the SparkFun MP3 Shield.
  Pins 0, 1, 5, 10, A0, A1, A2, A3, and A4 are setup to trigger tracks
  "track001.mp3", "track002.mp3", etc. on an SD card loaded into
  the shield. Whenever any of those pins are shorted to ground,
  their respective track will start playing.

  When a new pin is triggered, any track currently playing will
  stop, and the new one will start.

  A5 is setup to globally STOP playing a track when triggered.

  If you need more triggers, the shield's jumpers on pins 3 and 4
  (MIDI-IN and GPIO1) can be cut open and used as additional
  trigger pins. Also, because pins 0 and 1 are used as triggers
  Serial is not available for debugging. Disable those as
  triggers if you want to use serial.

  Much of this code was grabbed from the FilePlayer example
  included with the SFEMP3Shield library. Major thanks to Bill
  Porter and Michael Flaga, again, for this amazing library!

  ______________________________________________________________

  Modified By: Levi Butcher
  Source of original file: https://learn.sparkfun.com/tutorials/mp3-player-shield-hookup/example-sketch-mp3-trigger
  Modification Notes:
    Changed the #include<SFEMP3Shield.h> to #include <vs1053_SdFat.h>
    Changed the SFEMP3Shield MP3player to vs1053 MP3player

  Current Libraries version at time of modification (Names our exact from Arduino Library Manager):
    VS1053 for use with Sdfat -> Version 1.3.0

  Usage Notes:
    Files need to be uploaded to a microSD card formatted as FAT32
    Each MP3 file must be labeled as trackXXX.mp3
    The XXX will correspond to a pin on the MP3 Shield, when it is shorted to ground, that corresponding track will play
    This file as of now only uses pins {0, 1, 5, 10, A0, A1, A2, A3, A4} that is 9 tracks that can be played
    Tracks should be labeled track001.mp3 to track010.mp3

    If you want to add more tracks, add more digital pins to the array triggerPins,
    and upload more tracks to the SD card incrementing the file number accordingly
*/

#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library
#include <vs1053_SdFat.h>  // Mp3 Shield Library

SdFat sd; // Create object to handle SD functions

vs1053 MP3player; // Create Mp3 library object
// These variables are used in the MP3 initialization to set up
// some stereo options:
const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)
const uint16_t monoMode = 0;  // Mono setting 0=off, 3=max

/* Pin setup */
#define TRIGGER_COUNT 9

int triggerPins[TRIGGER_COUNT] = {0, 1, 5, 10, A0, A1, A2, A3, A4};

int stopPin = A5; // This pin triggers a track stop.
int lastTrigger = 0; // This variable keeps track of which tune is playing

void setup()
{
  /* Set up all trigger pins as inputs, with pull-ups activated: */
  for (int i=0; i<TRIGGER_COUNT; i++)
  {
    pinMode(triggerPins[i], INPUT_PULLUP);
  }
  pinMode(stopPin, INPUT_PULLUP);




  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
}

// All the loop does is continuously step through the trigger
//  pins to see if one is pulled low. If it is, it'll stop any
//  currently playing track, and start playing a new one.
void loop()
{
  for (int i=0; i<TRIGGER_COUNT; i++)
  {
    if ((digitalRead(triggerPins[i]) == LOW) && ((i+1) != lastTrigger))
    {
      lastTrigger = i+1; // Update lastTrigger variable to current trigger
      // Test this clause with the blink() functionality
      /* If another track is playing, stop it: */
      if (MP3player.isPlaying())
      {
        MP3player.stopTrack();
        // Test this clause with the blink() functionality
      }


      /* Use the playTrack function to play a numbered track: */
        uint8_t result = MP3player.playTrack(lastTrigger);

      // An alternative here would be to use the
      //  playMP3(fileName) function, as long as you mapped
      //  the file names to trigger pins.

      if (result == 0)  // playTrack() returns 0 on success
      {
        // Success
        // Test this clause with the blink() functionality
      }
      else // Otherwise there's an error, check the code
      {
        // Print error code somehow, someway
      }
    }
  }
  // After looping through and checking trigger pins, check to
  //  see if the stopPin (A5) is triggered.
  if (digitalRead(stopPin) == LOW)
  {
    lastTrigger = 0; // Reset lastTrigger
    // If another track is playing, stop it.
    if (MP3player.isPlaying())
      MP3player.stopTrack();
  }
}

// initSD() initializes the SD card and checks for an error.
void initSD()
{
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED))
    sd.initErrorHalt();
  if(!sd.chdir("/"))
    sd.errorHalt("sd.chdir");
}

// initMP3Player() sets up all of the initialization for the
// MP3 Player Shield. It runs the begin() function, checks
// for errors, applies a patch if found, and sets the volume/
// stero mode.
void initMP3Player()
{
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  if(result != 0) // check result, see readme for error codes.
  {
    // Error checking can go here!
  }
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}
