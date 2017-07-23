// -------------- PIXEL DATA FOR CUSTOM CHARS ----------------
byte rightEar[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01100,
  B01110,
  B00111,
  B00011,
};

byte leftEar[8] = {
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

// -----------------------------------------------------------

void drawPet(int expression) {
  lcd.clear();
  drawEarsAt(7,0);
  drawFace(expression);
}

void drawEarsAt(int lcdRow,int lcdCol) {
  lcd.createChar(0,rightEar);
  lcd.createChar(1,leftEar);
  
  lcd.setCursor(lcdRow,lcdCol);
  lcd.write(byte(RIGHT_EAR));
  lcd.print("_"); 
  lcd.write(byte(LEFT_EAR));
}

void drawFace(int expression) {
  lcd.createChar(2,smile);
  lcd.createChar(3,grin);
  lcd.createChar(4,frown);
  
  lcd.setCursor(7,1);
  lcd.print("(");
  lcd.setCursor(8,1);
  if(expression == OPEN_MOUTH) { 
    lcd.print((char)239); //use ö for facial expression 
  }
  lcd.write(byte(expression));
  lcd.setCursor(9,1);
  lcd.print(")");
}

void drawPoop() {
  lcd.createChar(5,poo);
  lcd.setCursor(12,1);
  lcd.write(byte(POOP));
}

void drawWaterAt(int lcdRow, int lcdCol) {
  lcd.createChar(6,water);
  lcd.setCursor(lcdRow,lcdCol);
  lcd.write(byte(WATER));
  playSound(bathTone,thirtySecondNotes);
  delay(400);
}

void drawChicken() {
  lcd.createChar(7,chicken);
  lcd.setCursor(11,1);
  lcd.write(byte(CHICKEN));
}

void drawSparkleAt(int lcdRow, int lcdCol) {
  lcd.setCursor(lcdRow,lcdCol);
  lcd.print((char)235);
}

void drawEating() { 
  for(int i = 0; i < 3; i++) {
    drawPet(OPEN_MOUTH);
    drawChicken();
    playSound(eatingTone,thirtySecondNotes);
    delay(450);

    drawPet(SMILING);
    drawChicken();
    playSound(eatingTone,thirtySecondNotes);
    delay(450);
  }
  drawPet(GRINNING);
  lcd.setCursor(11,1);
  lcd.print((char)222);
}

void drawBathing() {
  for(int i = 0; i < 2; i++) {
    drawWaterAt(6,0);
    drawWaterAt(10,1);
    
    clearCharAt(6,0);    
    clearCharAt(10,1);
    
    drawWaterAt(10,0);    
    drawWaterAt(6,1);

    clearCharAt(10,0);
    clearCharAt(6,1);
  }
  
  if(petHasPooped) {
    //remove the poop pile from the screen
    clearCharAt(12,1);
    petHasPooped = false;
  }
    
  delay(300);
  drawPet(GRINNING);
  playSound(bathDoneTone,eighthNotes);

  drawSparkleAt(10,0);
  drawSparkleAt(6,1);
  drawSparkleAt(12,1);
}

void drawSleeping() {
  lcd.clear();
  lcd.setCursor(11,0);
  lcd.print("zzZ");
  drawEarsAt(7,1);
}

void clearCharAt(int lcdRow, int lcdCol) {
  lcd.setCursor(lcdRow,lcdCol);
  lcd.print(" ");
}
