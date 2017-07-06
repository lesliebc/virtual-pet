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
      menuPresses++; 
    }
  }
}

/*
void menuOptions() {
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
    menuPresses = 2; //circle back to first menu option
    break;
  }
  
}
*/

void feed() {  
  lcd.clear();
  lcd.print(" o Feed     Bath");
  lcd.setCursor(0,1);
  lcd.print("   Rest     Exit");
  
  while(menuPresses == 2) {
    menuState = digitalRead(menuPin);
    if(menuState == LOW) { 
      //pressButtonTone();
      playSound(buttonPressTone,thirtySecondNotes);
      menuPresses++;
      delay(200);
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
      playSound(buttonPressTone,thirtySecondNotes); 
      menuPresses++;
      delay(200);
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
      playSound(buttonPressTone,thirtySecondNotes);
      menuPresses++;
      delay(200);
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
        playSound(buttonPressTone,thirtySecondNotes);
        menuPresses++;
        delay(200);
      }
  }
}
