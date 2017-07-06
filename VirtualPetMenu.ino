/* When the menu button is pressed once, display the
 *  first menu screen containing usage instructions
 */
void menuStart() {
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

void menuOptions() {
  lcd.print("   Feed     Bath");
  lcd.setCursor(0,1);
  lcd.print("   Rest     Exit");
}

void feed() {  
  drawPet(2);
  drawChicken();
  drawEating();
  lcd.clear();
  menuOptions();
}

void rest() {
  drawSleeping();
  snoringTone();
  exitMenu();
}

void bath() {
  drawPet(2);
  if(pooped) { drawPoop(); }
  drawBathing();
  lcd.clear();
  menuOptions();
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
