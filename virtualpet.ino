#include <LiquidCrystal.h>
#include "pitches.h"

LiquidCrystal lcd(0,1,8,9,10,11);
const int menuPin = 2;
const int selectPin = 12;
const int piezoPin = 4;

int welcomeNotes[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int bathDoneNotes[] = { NOTE_E3, NOTE_F4, NOTE_AS4, NOTE_GS5 };
int eighthNotes[] = { 8, 8, 8, 8 };

int buttonPressNotes[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int eatingNotes[] = { NOTE_DS4, NOTE_F4, NOTE_DS4, NOTE_B3 };
int bathNotes[] = { NOTE_D5, NOTE_E5, NOTE_F5, NOTE_A5 };
int thirtySecondNotes[] = { 32, 32, 32, 32 };

int poopNotes[] = { NOTE_B0, NOTE_A3, NOTE_B0, NOTE_B0 };
int poopNoteDurations[] = { 4, 8, 8, 4 };

//flags
int pooped = false; //keep track of buddy's waste of course
int onHomeScreen = true; //true since this is the default view

int menuState = HIGH; //the state of the left button, used for toggling menu options
int selectState = HIGH; //the state of the right button, used for selecting menu options

unsigned long prev_move = 0;
unsigned long move_delay = 700;

int menuPresses = 0;
int count = 0;

byte ear1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01100,
  B01110,
  B00111,
  B00011,
};

byte ear2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00110,
  B01110,
  B11100,
  B11000,
};

byte smile[8] = {
  B00000,
  B00000,
  B10001,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000,
};

byte grin[8] = {
  B00000,
  B00000,
  B10001,
  B00000,
  B11111,
  B01110,
  B00000,
  B00000,
};

byte frown[8] = {
  B00000,
  B00000,
  B10001,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000,
};

byte poo[8] = {
  B00000,
  B00000,
  B00000,
  B10000,
  B01100,
  B01110,
  B11111,
  B11111,
};

byte water[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00000,
  B00000,
};

byte chicken[8] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B01100,
  B01000,
  B10100,
};


void setup() {
  pinMode(menuPin,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  lcd.begin(16,2);

  //startup screen
  lcd.clear();
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("VIRTUAL PET");
  lcd.setCursor(0,1);
  delay(2500);
  lcd.print("by Leslie Cheung");
  delay(2000);

  drawPet(2); //smile

  welcomeTone();
}

void loop() { 
  menuState = digitalRead(menuPin);
    
  if(menuState == LOW) {
    menuPresses++;
    onHomeScreen = false;
    delay(250);
  }

  if(onHomeScreen) { pet_movements(); }

  //event handling for menu button presses
  switch(menuPresses) {
    case 1:
    menuStart();
    break;
    case 2:
    feed();
    break;
    case 3:
    rest();
    break;
    case 4:
    bath();
    break;
    case 5:
    exitMenu();
    break;
    case 6:
    menuPresses = 2;
    break;
  }
}

void pet_movements() {
  if(!onHomeScreen) { return; } // only want to scroll if on home screen
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
  if(currentTime % 30000 == 0 && pooped == false) {
    drawPet(4); //change mood to frown
    drawPoop();
    pooped = true;
    poopAlertTone();
  }
}


void menuStart() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PET CARE MENU");
  lcd.setCursor(0,1);
  lcd.print("Push to continue");

  while(menuPresses == 1) {
    menuState = digitalRead(menuPin);
    if(menuState == LOW) { 
      delay(250);
      menuPresses++; 
    }
  }
}

void feed() {  
  lcd.clear();
  lcd.print(" o Feed     Bath");
  lcd.setCursor(0,1);
  lcd.print("   Rest     Exit");
  
  while(menuPresses == 2) {
    menuState = digitalRead(menuPin);
    if(menuState == LOW) { 
      pressButtonTone();
      menuPresses++;
      delay(250);
      break;
    }
    selectState = digitalRead(selectPin);
    if(selectState == LOW) {
      drawPet(2);
      drawChicken();
      drawEating();
    }
  }
}

void rest() {
  lcd.clear();
  lcd.print("   Feed     Bath");
  lcd.setCursor(0,1);
  lcd.print(" o Rest     Exit");
  while(menuPresses == 3) {
    menuState = digitalRead(menuPin);
    if(menuState == LOW) {
      pressButtonTone(); 
      menuPresses++;
      delay(250);
      break;
    }
    selectState = digitalRead(selectPin);
    if(selectState == LOW) {
      drawSleeping();
      snoringTone();
      drawPet(2);
      onHomeScreen = true;
      menuPresses = 0;
    }
  }
}

void bath() {
  lcd.clear();
  lcd.print("   Feed   o Bath");
  lcd.setCursor(0,1);
  lcd.print("   Rest     Exit");
  while(menuPresses == 4) {
    menuState = digitalRead(menuPin);
    if(menuState == LOW) {
      pressButtonTone();
      menuPresses++;
      delay(250);
      break;
    }
    selectState = digitalRead(selectPin);
    if(selectState == LOW) {
      drawBathing();
    }
  }
}

void exitMenu() {
  lcd.clear();
  lcd.print("   Feed     Bath");
  lcd.setCursor(0,1);
  lcd.print("   Rest   o Exit");
  while(menuPresses == 5) {
    selectState = digitalRead(selectPin);
      if(selectState == LOW) {
        if(pooped) {
          drawPet(4);
          drawPoop();
        }
        else { drawPet(2); }
        menuPresses = 0;
        onHomeScreen = true;
      }
      menuState = digitalRead(menuPin);
      if(menuState == LOW) {
        pressButtonTone();
        menuPresses++;
        delay(250);
      }
  }
}


void drawPet(int expression) {
  lcd.clear();
  lcd.createChar(0,ear1);
  lcd.createChar(1,ear2);
  lcd.createChar(2,smile);
  lcd.createChar(3,grin);
  lcd.createChar(4,frown);
 
  //ears
  lcd.setCursor(7,0);
  lcd.write(byte(0));
  lcd.setCursor(9,0);
  lcd.write(byte(1));

  //head
  lcd.setCursor(8,0);
  lcd.print("_");

  //face
  lcd.setCursor(7,1);
  lcd.print("(");
  lcd.setCursor(8,1);
  if(expression == 5) { 
    lcd.print((char)239); //use ö for facial expression 
  }
  lcd.write(byte(expression)); //facial expression
  lcd.setCursor(9,1);
  lcd.print(")");
}

void drawPoop() {
  lcd.createChar(5,poo);
  lcd.setCursor(12,1);
  lcd.write(byte(5));
}

void drawChicken() {
  lcd.createChar(7,chicken);
  lcd.setCursor(11,1);
  lcd.write(byte(7));
}

void drawEating() { 
  for(int i = 0; i < 3; i++) {
    drawPet(5);
    drawChicken();
    eatingTone();
    
    delay(450);

    drawPet(2);
    drawChicken();
    eatingTone();
    delay(450);
  }
  drawPet(3);
  lcd.setCursor(11,1);
  lcd.print((char)222);
  
  delay(2500);
  loop();
}

void drawBathing() {
  lcd.createChar(6,water);

  drawPet(2);
  if(pooped) { drawPoop(); }
  
  for(int i = 0; i < 2; i++) {
    lcd.setCursor(6,0);
    lcd.write(byte(6));
    bathingTone();
    delay(400);

    lcd.setCursor(10,1);
    lcd.write(byte(6));
    bathingTone();
    delay(400);

    lcd.setCursor(6,0);
    lcd.print(" ");

    lcd.setCursor(10,1);
    lcd.print(" ");
    
    lcd.setCursor(10,0);
    lcd.write(byte(6));
    bathingTone();
    delay(400);
    
    lcd.setCursor(6,1);
    lcd.write(byte(6));
    bathingTone();
    delay(400);

    lcd.setCursor(10,0);
    lcd.print(" ");

    lcd.setCursor(6,1);
    lcd.print(" ");
  }
  lcd.setCursor(12,1);
  lcd.print(" ");

  delay(300);
  lcd.clear();
  pooped = false;
  drawPet(3);
  bathDoneTone();

  lcd.setCursor(10,0);
  lcd.print((char)235);
  lcd.setCursor(6,1);
  lcd.print((char)235);
  lcd.setCursor(12,1);
  lcd.print((char)235);
  
  delay(2500);
  loop();
}

void drawSleeping() {
  lcd.clear();
  lcd.setCursor(11,0);
  lcd.print("zzZ");
  lcd.setCursor(7,1);
  lcd.write(byte(0));
  lcd.setCursor(9,1);
  lcd.write(byte(1));
  lcd.setCursor(8,1);
  lcd.print("_");
}

void welcomeTone() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / eighthNotes[thisNote];
    tone(piezoPin, welcomeNotes[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(piezoPin);
  }
}

void pressButtonTone() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / thirtySecondNotes[thisNote];
    tone(piezoPin, buttonPressNotes[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(piezoPin);
  } 
}

void eatingTone() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / thirtySecondNotes[thisNote];
    tone(piezoPin, eatingNotes[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(piezoPin);
  } 
}

void poopAlertTone() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / poopNoteDurations[thisNote];
    tone(piezoPin, poopNotes[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(piezoPin);
  }
}

void bathingTone() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / thirtySecondNotes[thisNote];
    tone(piezoPin, bathNotes[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(piezoPin);
  } 
}

void bathDoneTone() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / eighthNotes[thisNote];
    tone(piezoPin, bathDoneNotes[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(piezoPin);
  }
}

void snoringTone() {
  for(int i = 0; i < 3; i++) {
    tone(piezoPin, NOTE_B0, 1000);
    delay(2000);
  }
  noTone(piezoPin);
  delay(4000);
}


