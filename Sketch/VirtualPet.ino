#include <LiquidCrystal.h>
#include "pitches.h"

// ---------------- CONSTANTS FOR PIXEL ART ------------------
#define RIGHT_EAR 0
#define LEFT_EAR 1
#define SMILING 2
#define GRINNING 3
#define FROWNING 4
#define POOP 5
#define WATER 6
#define CHICKEN 7
#define OPEN_MOUTH 8

// ------------------- BREADBOARD SETUP ----------------------
LiquidCrystal lcd(0,1,8,9,10,11);
const int menuPin = 2;
const int selectPin = 12;
const int piezoPin = 4;

// ------------------ PUSH-BUTTON STATES ---------------------
int menuState = HIGH;
int selectState = HIGH;
int menuPresses = 0;

// ------------------------- FLAGS ---------------------------
int petHasPooped = false;
int onHomeScreen = true;

// ---------------- SOUNDS & NOTE DURATIONS ------------------
int welcomeTone[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int bathDoneTone[] = { NOTE_E3, NOTE_F4, NOTE_AS4, NOTE_GS5 };
int eighthNotes[] = { 8, 8, 8, 8 };

int buttonPressTone[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int eatingTone[] = { NOTE_DS4, NOTE_F4, NOTE_DS4, NOTE_B3 };
int bathTone[] = { NOTE_D5, NOTE_E5, NOTE_F5, NOTE_A5 };
int thirtySecondNotes[] = { 32, 32, 32, 32 };

int poopTone[] = { NOTE_B0, NOTE_A3, NOTE_B0, NOTE_B0 };
int quarterAndEighthNotes[] = { 4, 8, 8, 4 };

int snoring[] = { NOTE_B0, 0, NOTE_B0, 0 };
int wholeNotes[] = { 1, 1, 1, 1 };

// -----------------------------------------------------------


void setup() {
  pinMode(menuPin,INPUT_PULLUP);
  pinMode(selectPin,INPUT_PULLUP);
  lcd.begin(16,2);
  drawPet(SMILING);
  playSound(welcomeTone,eighthNotes);
}

void loop() {
  unsigned long currentTime = millis();

  menuState = digitalRead(menuPin);
  selectState = digitalRead(selectPin);

  if(menuState == LOW) {
    menuPresses++;
    menuButtonPress();
  }

  menuButtonListener();
 
  if(onHomeScreen) { 
    timePetMovements(currentTime);
    timePetPooping(currentTime);
  }
}

