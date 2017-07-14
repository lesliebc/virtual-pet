#include <LiquidCrystal.h>
#include "pitches.h"

LiquidCrystal lcd(0,1,8,9,10,11);
const int menuPin = 2;
const int selectPin = 12;
const int piezoPin = 4;

int welcomeTone[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int bathDoneTone[] = { NOTE_E3, NOTE_F4, NOTE_AS4, NOTE_GS5 };
int eighthNotes[] = { 8, 8, 8, 8 };

int buttonPressTone[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int eatingTone[] = { NOTE_DS4, NOTE_F4, NOTE_DS4, NOTE_B3 };
int bathTone[] = { NOTE_D5, NOTE_E5, NOTE_F5, NOTE_A5 };
int thirtySecondNotes[] = { 32, 32, 32, 32 };

int poopTone[] = { NOTE_B0, NOTE_A3, NOTE_B0, NOTE_B0 };
int quarterAndEighthNotes[] = { 4, 8, 8, 4 };

int pooped = false;
int onHomeScreen = true;

int menuState = HIGH; //the state of the left button, used for toggling menu options
int selectState = HIGH; //the state of the right button, used for selecting menu options

unsigned long prev_move = 0;
unsigned long move_delay = 700;

int menuPresses = 0;
int count = 0;

void setup() {
  pinMode(menuPin,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  lcd.begin(16,2);
  drawPet(2); //smile
  playSound(welcomeTone,eighthNotes);
}

void loop() { 
  menuState = digitalRead(menuPin);
  selectState = digitalRead(selectPin);
    
  if(menuState == LOW) {
    menuPresses++;
    playSound(buttonPressTone,thirtySecondNotes);
    onHomeScreen = false;
    delay(250);
  }
  
  switch(menuPresses) {
    case 1:
    lcd.clear();
    showMenuIntro();
    break;
    case 2:
    showMenuOptions();
    break;
    case 3:
    lcd.setCursor(10,1);
    lcd.print(" ");
    lcd.setCursor(1,0);
    lcd.print("o");
    if(selectState == LOW) { feed(); }
    break;
    case 4:
    lcd.setCursor(1,0);
    lcd.print(" ");
    lcd.setCursor(1,1);
    lcd.print("o");
    if(selectState == LOW) { rest(); }
    break;
    case 5:
    lcd.setCursor(1,1);
    lcd.print(" ");
    lcd.setCursor(10,0);
    lcd.print("o");
    if(selectState == LOW) { bath(); }
    break;
    case 6:
    lcd.setCursor(10,0);
    lcd.print(" ");
    lcd.setCursor(10,1);
    lcd.print("o");
    if(selectState == LOW) { exitMenu(); }
    break;
    case 7:
    menuPresses = 3; //circle back to first menu option
    break;
  }

  if(onHomeScreen) { pet_movements(); }
}

void pet_movements() {
  unsigned long currentTime = millis();
  if(currentTime - prev_move >= move_delay) {
    prev_move = currentTime;
    if(count < 3) {
      lcd.scrollDisplayLeft();
      count++;
    }
    else if(count < 6) {
      lcd.scrollDisplayRight();
      count++;
    }
    else { count = 0; }
  }
  if(currentTime % 30000 == 0 && !pooped) {
    drawPet(4); //change mood to frown
    drawPoop();
    pooped = true;
    playSound(poopTone,quarterAndEighthNotes);
  }
}
