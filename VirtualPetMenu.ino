void menuButtonPress() {
  playSound(buttonPressTone,thirtySecondNotes);
  if(onHomeScreen) { onHomeScreen = false; }
}

void navigateMenu() {
  switch(menuPresses) {
    case 1:
    showMenuIntro();
    break;
    
    case 2:
    showMenuOptions();
    clearCharAt(10,1); // remove previous menu pointer
    setPointerTo(1,0); // set the pointer here instead
    if(selectState == LOW) { feed(); }
    break;
    
    case 3:
    clearCharAt(1,0);
    setPointerTo(1,1);
    if(selectState == LOW) { rest(); }
    break;
    
    case 4:
    clearCharAt(1,1);
    setPointerTo(10,0);
    if(selectState == LOW) { bath(); }
    break;
    
    case 5:
    clearCharAt(10,0);
    setPointerTo(10,1);
    if(selectState == LOW) { exitMenu(); }
    break;
    
    case 6:
    menuPresses = 2; // circle back to first menu option
    break;
  }
}

void setPointerTo(int lcdRow, int lcdCol) {
  lcd.setCursor(lcdRow,lcdCol);
  lcd.print("o");
}

void showMenuIntro() {
  lcd.clear();
  lcd.print("PET CARE MENU");
  lcd.setCursor(0,1);
  lcd.print("Push to continue");

  while(menuPresses == 1) {
    menuState = digitalRead(menuPin);
    if(menuState == LOW) { 
      delay(200);
      lcd.clear();
      menuPresses++;
    }
  }
}

void showMenuOptions() {
  lcd.setCursor(3,0);
  lcd.print("Feed     Bath");
  lcd.setCursor(3,1);
  lcd.print("Rest     Exit");
}

void feed() {  
  drawPet(SMILING);
  drawChicken();
  drawEating();
  delay(2500);
  lcd.clear();
  showMenuOptions();
}

void rest() {
  drawSleeping();
  snoringTone();
  delay(4500);
  exitMenu();
}

void bath() {
  drawPet(SMILING);
  if(petHasPooped) { drawPoop(); }
  drawBathing();
  delay(2500);
  lcd.clear();
  showMenuOptions();
}

void exitMenu() {
  if(petHasPooped) {
    drawPet(FROWNING);
    drawPoop();
  }
  else { drawPet(SMILING); }
  menuPresses = 0;
  onHomeScreen = true;
}
