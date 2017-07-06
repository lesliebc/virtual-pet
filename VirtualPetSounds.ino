#define SONG_LENGTH  4

void playSound(int melody[], int noteDurations[]) {
  for (int thisNote = 0; thisNote < SONG_LENGTH; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(piezoPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
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
