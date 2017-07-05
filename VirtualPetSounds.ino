int welcomeNotes[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int bathDoneNotes[] = { NOTE_E3, NOTE_F4, NOTE_AS4, NOTE_GS5 };
int eighthNotes[] = { 8, 8, 8, 8 };

int buttonPressNotes[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
int eatingNotes[] = { NOTE_DS4, NOTE_F4, NOTE_DS4, NOTE_B3 };
int bathNotes[] = { NOTE_D5, NOTE_E5, NOTE_F5, NOTE_A5 };
int thirtySecondNotes[] = { 32, 32, 32, 32 };

int poopNotes[] = { NOTE_B0, NOTE_A3, NOTE_B0, NOTE_B0 };
int poopNoteDurations[] = { 4, 8, 8, 4 };

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
