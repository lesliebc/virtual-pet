void showMenuIntro() {
  lcd.clear();
  lcd.setCursor(0,0);
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
  lcd.print("   Feed     Bath");
  lcd.setCursor(0,1);
  lcd.print("   Rest     Exit");
}

void feed() {  
  drawPet(2);
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
  drawPet(2);
  if(pooped) { drawPoop(); }
  drawBathing();
  delay(2500);
  lcd.clear();
  showMenuOptions();
}

void exitMenu() {
  if(pooped) {
    drawPet(4);
    drawPoop();
  }
  else { drawPet(2); }
  menuPresses = 0;
  onHomeScreen = true;
}
