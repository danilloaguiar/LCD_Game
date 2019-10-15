/*
                                                SDA                    SCL
      Blue Pill, STM32F103xxxx boards.......... PB7                    PB6 
*/

#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

#define eixoY PA1
#define LED PC13

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t toy1[8] = {0b00110,	0b00110,	0b00000,	0b11110,	0b01111,	0b01100,	0b11100,	0b10110};

uint8_t toy2[8] = {0b01100,	0b01100,	0b00000,	0b01111,	0b11110,	0b01100,	0b10010,	0b11011};

uint8_t tjb[8] = {0b10010, 0b10100,	0b11000,	0b10000,	0b11000,	0b10101,	0b10011,	0b10111};

bool position = false;
bool toy = false;
bool o0 = false, o1 = false, o2 = false, o3 = false;
bool i0 = true, i1 = true, i2 = true, i3 = true;



class transistor {
  public:
    int position = 16;
    int linha;
    transistor();
    void andar();
    void restart();
};

transistor::transistor(){

}

void transistor::andar() {
  lcd.setCursor(position, linha);
  lcd.print(" ");
  position = position - 1;
  lcd.setCursor(position, linha);
  lcd.write((byte)2);
}
void transistor::restart(){
  lcd.setCursor(0, linha);
  lcd.print(" ");
  position = 16;
  
}

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
    delay(450);
  }
}


void running(){

  if (position){
    lcd.setCursor(0,0);
    if (toy){
      lcd.write((byte)0);
      toy = false;
    }
    else{
      lcd.write((byte)1);
      toy = true;
    }
  }
  else if (!position)  {
    lcd.setCursor(0,1);
    if (toy){
      lcd.write((byte)0);
      toy = false;
    }
    else{
      lcd.write((byte)1);
      toy = true;
    }
  }

}

void obstaculos(){
  static transistor t0;
  static transistor t1;
  static transistor t2;
  static transistor t3;
  
  if(millis() > 7000 && i0){
    t0.linha = 0;
    t0.andar();
    i0 = false;
    o0 = true;
  }
  if(millis() > 10000 && i1){
    t1.linha = 1;
    t1.andar();
    i1 = false;
    o1 = true;
  }
  if(millis() > 12500 && i2){
    t2.linha = 0;
    t2.andar();
    i2 = false;
    o2 = true;
  }
  if(millis() > 14900 && i3){
    t3.linha = 1;
    t3.andar();
    i3 = false;
    o3 = true;
  }

  if(o0){
    t0.andar();
    if(t0.position<0){
      t0.restart();
    }
  }
  if(o1){
    t1.andar();
    if(t1.position<0){
      t1.restart();
    }
  }
  if(o2){
    t2.andar();
    if(t2.position<0){
      t2.restart();
    }
  }
  if(o3){
    t3.andar();
    if(t3.position<0){
      t3.restart();
    }
  }

  delay(100);
}


void setup()
{
  lcd.init();                      // initialize the lcd 
  
  pinMode(LED, OUTPUT);


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

  lcd.setCursor(0,1);
  lcd.write((byte)0);
}


void loop()
{ 
  if ((analogRead(eixoY)) > 800){ 
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(0,0);
    lcd.write((byte)0);
    toy = false;
    position = true;
  }
  else if ((analogRead(eixoY)) < 200){
    lcd.setCursor(0,1);
    lcd.write((byte)0);
    toy = false;
    lcd.setCursor(0,0);
    lcd.print(" ");
    position = false;
  } 

  running();
  obstaculos();
  
  delay(400);
}