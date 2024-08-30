#include "LCD.hpp"

MyLCD::MyLCD() { internLCD = new LiquidCrystal_I2C(0x27, 16, 2); }

void MyLCD::initLCD() {
    internLCD->init();
    internLCD->backlight();
    // 0 = id entry //utiliser lcd.setCursor(0, 0);
    // lcd.write(0); pour ecrire le char
    internLCD->createChar(0, skullHead);
    affiche("Hello !", LCD_LINE_UP);
    delay(1000);
    internLCD->clear();
}

void MyLCD::affiche(String lineStr, int line) {
    internLCD->setCursor(0, line);
    internLCD->printstr(lineStr.c_str());
}

void MyLCD::append(String lineStr, int posCur, int line) {
    internLCD->setCursor(posCur, line);
    internLCD->printstr(lineStr.c_str());
}

void MyLCD::posCur(int y, int x) { internLCD->setCursor(y, x); }

void MyLCD::setBrightnessOn(bool on) {
    if (on) {
        internLCD->backlight();
    } else {
        internLCD->noBacklight();
    }
}

MyLCD::~MyLCD() { delete internLCD; }