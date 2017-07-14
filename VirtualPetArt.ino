//pixel data for custom glyphs used in animations
//right ear
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

//left ear
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

//smiling facial expression
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

//grinning facial expression
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

//frowning facial expression
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

//water droplet used for 'bath' animation
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

//chicken drumstick used for 'feed' animation
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

void drawPet(int expression) {
  lcd.clear();
  drawEars(7,0);
  drawFace(expression);
}

void drawEars(int lcdRow,int lcdCol) {
  lcd.createChar(0,ear1);
  lcd.createChar(1,ear2);
  
  lcd.setCursor(lcdRow,lcdCol);
  lcd.write(byte(0));
  lcd.print("_"); 
  lcd.write(byte(1));
}

void drawFace(int expression) {
  lcd.createChar(2,smile);
  lcd.createChar(3,grin);
  lcd.createChar(4,frown);
  
  lcd.setCursor(7,1);
  lcd.print("(");
  lcd.setCursor(8,1);
  if(expression == 5) { 
    lcd.print((char)239); //use ö for facial expression 
  }
  lcd.write(byte(expression));
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
    playSound(eatingTone,thirtySecondNotes);
    delay(450);

    drawPet(2);
    drawChicken();
    playSound(eatingTone,thirtySecondNotes);
    delay(450);
  }
  drawPet(3);
  lcd.setCursor(11,1);
  lcd.print((char)222);
}

void drawBathing() {
  lcd.createChar(6,water);
  
  for(int i = 0; i < 2; i++) {
    lcd.setCursor(6,0);
    lcd.write(byte(6));
    playSound(bathTone,thirtySecondNotes);
    delay(400);

    lcd.setCursor(10,1);
    lcd.write(byte(6));
    playSound(bathTone,thirtySecondNotes);
    delay(400);

    lcd.setCursor(6,0);
    lcd.print(" ");

    lcd.setCursor(10,1);
    lcd.print(" ");
    
    lcd.setCursor(10,0);
    lcd.write(byte(6));
    playSound(bathTone,thirtySecondNotes);
    delay(400);
    
    lcd.setCursor(6,1);
    lcd.write(byte(6));
    playSound(bathTone,thirtySecondNotes);
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
  playSound(bathDoneTone,eighthNotes);

  lcd.setCursor(10,0);
  lcd.print((char)235);
  lcd.setCursor(6,1);
  lcd.print((char)235);
  lcd.setCursor(12,1);
  lcd.print((char)235);
}

void drawSleeping() {
  lcd.clear();
  lcd.setCursor(11,0);
  lcd.print("zzZ");
  drawEars(7,1);
}
