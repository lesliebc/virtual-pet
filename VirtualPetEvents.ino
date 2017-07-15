unsigned long prevMove = 0;
unsigned long moveDelay = 700;
int timesMoved = 0;

void timePetMovements(unsigned long currentTime) {
  if(currentTime - prevMove >= moveDelay) {
    prevMove = currentTime;
    if(timesMoved < 3) {
      lcd.scrollDisplayLeft();
      timesMoved++;
    }
    else if(timesMoved < 6) {
      lcd.scrollDisplayRight();
      timesMoved++;
    }
    else { timesMoved = 0; }
  }
}

void timePetPooping(unsigned long currentTime) {
  if(currentTime % 30000 == 0 && !pooped) {
    drawPet(FROWNING);
    drawPoop();
    pooped = true;
    playSound(poopTone,quarterAndEighthNotes);
  }
}
