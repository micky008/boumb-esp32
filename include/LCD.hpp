#ifndef _MY_LCD__
#define _MY_LCD__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define LCD_LINE_UP 0
#define LCD_LINE_DOWN 1

class MyLCD {
   public:
    MyLCD();
    ~MyLCD();
    void initLCD();
    void affiche(String lineStr, int line);
    void append(String lineStr, int posCur, int line);
    void posCur(int y, int x);
    void setBrightnessOn(bool on);
   private:
    LiquidCrystal_I2C *internLCD;
    byte skullHead[8] = {0b00000, 0b01110, 0b10101, 0b11111,
                         0b01010, 0b01010, 0b01110, 0b00000};
};

#endif