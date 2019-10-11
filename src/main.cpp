#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t toy1[8] = {0b00110,	0b00110,	0b00000,	0b11110,	0b01111,	0b01100,	0b11100,	0b10110};

uint8_t toy2[8] = {0b01100,	0b01100,	0b00000,	0b01111,	0b11110,	0b01100,	0b10010,	0b11011};

uint8_t tjb[8] = {0b10010, 0b10100,	0b11000,	0b10000,	0b11000,	0b10101,	0b10011,	0b10111};

void initGame(){
  
  for (int x = 0; x < 16; x += 1) {
    lcd.clear();  
    if (x==8){
      lcd.setCursor(8,0);
      lcd.write((byte)1);
    }
    else{
      lcd.setCursor(x,1);
      if (x%2 == 0){
        lcd.write((byte)0);
      }
      else{
        lcd.write((byte)1);
      }
    }
    lcd.setCursor(16-x,1);
    lcd.write((byte)2);
    delay(350);
  }
}

void setup()
{
  lcd.init();                      // initialize the lcd 
  
  lcd.createChar(0, toy1);
  lcd.createChar(1, toy2);
  lcd.createChar(2, tjb);
  lcd.home();

  // Print a message to the LCD.
  lcd.backlight();
  
  initGame();

  lcd.setCursor(3,0);
  lcd.print("LCD GAME");
  lcd.setCursor(0,1);
  lcd.print("By: Danillo Aguiar");
  delay(3000);
  lcd.clear();
}



void loop()
{ 
  initGame();
}