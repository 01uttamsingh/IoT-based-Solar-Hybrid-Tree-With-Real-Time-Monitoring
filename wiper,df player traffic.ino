#include "Arduino.h"
#include "SpeakerStereo3W.h"
#include<Servo.h>
#define STEREOSPEAKER_PIN_POS	2

Servo servo1;
unsigned int StereoSpeakerHoorayLength          = 6;                                                      // amount of notes in melody
unsigned int StereoSpeakerHoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int StereoSpeakerHoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!

SpeakerStereo3W StereoSpeaker(STEREOSPEAKER_PIN_POS);

void setup() {
  servo1.attach(6);
  
  softwareSerial.begin(9600);

  
}

void loop() {

  // SPEAKER -----------------------------
  StereoSpeaker.playMelody(StereoSpeakerHoorayLength, StereoSpeakerHoorayMelody, StereoSpeakerHoorayNoteDurations); 
    delay(500);  

  // WIPER-----------------------------------------
servo1.write(0);
delay(1000);
servo1.write(180);
delay(5000);
setdown();
loop1();
}
// TRAFFIC LIGHTS-------------------------------
int GREEN = 4;
int YELLOW = 5;
int RED = 7;
int DELAY_GREEN = 5000;
int DELAY_YELLOW = 2000;
int DELAY_RED = 5000;


// basic functions
void setdown()
{
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
}

void loop1()
{
  green_light();
  delay(DELAY_GREEN);
  yellow_light();
  delay(DELAY_YELLOW);
  red_light();
  delay(DELAY_RED);
}

void green_light()
{
  digitalWrite(GREEN, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
}

void yellow_light()
{
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(RED, LOW);
}

void red_light()
{
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, HIGH);
}
