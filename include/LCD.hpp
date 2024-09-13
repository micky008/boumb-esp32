#ifndef _MY_LCD__
#define _MY_LCD__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "interfaces/Initialisation.hpp"
#include "interfaces/options/OLCD.hpp"

#define LCD_LINE_UP 0
#define LCD_LINE_DOWN 1

#define NBROW 2
#define NBCOL 16

class MyLCD : public Initialisation {
   public:
    MyLCD();
    ~MyLCD();
    void init();
    void applyOption(OptionLCD& options);
    void affiche(String lineStr, int line);
    void append(String lineStr, int posCur, int line);
    void posCur(int y, int x);
    void resetLine(int line);
    void clearAllScreen();
    void resetLineAfterPosition(int pos, int line);

   private:
    LiquidCrystal_I2C* internLCD;
    // byte skullHead[8] = {0b00000, 0b01110, 0b10101, 0b11111, 0b01010,
    // 0b01010, 0b01110, 0b00000};
};

#endif