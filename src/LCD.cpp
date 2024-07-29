#include "LCD.hpp"

MyLCD::MyLCD()
{
    internLCD = new LiquidCrystal_I2C(0x27, 16, 2);
}

void MyLCD::initLCD()
{
    internLCD->init();
    internLCD->backlight();
    internLCD->createChar(0, skullHead); // 0 = id entry //utiliser lcd.setCursor(0, 0); lcd.write(0); pour ecrire le char
    affiche("Hello !", LINE_UP);
    delay(1000);
    internLCD->clear();
}

void MyLCD::affiche(String lineStr, int line)
{
    internLCD->setCursor(0, line);
    internLCD->print(lineStr);
}

MyLCD::~MyLCD(){
    delete internLCD;
}