#include "LCD.hpp"

MyLCD::MyLCD() { internLCD = new LiquidCrystal_I2C(0x27, NBCOL, NBROW); }

void MyLCD::init() {
    internLCD->init();
    internLCD->backlight();
    // 0 = id entry //utiliser lcd.setCursor(0, 0);
    // lcd.write(0); pour ecrire le char
    // internLCD->createChar(0, skullHead);
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

void MyLCD::applyOption(OptionLCD& olcd) {
    if (olcd.getBrigtnessOn()) {
        internLCD->backlight();
    } else {
        internLCD->noBacklight();
    }
}

void MyLCD::resetLine(int line) {
    internLCD->setCursor(0, line);
    char lineChar[NBCOL];
    lineChar[NBCOL -1] = '\0';
    memset(lineChar, ' ', NBCOL - 1);
    internLCD->printstr(lineChar);
    internLCD->setCursor(line, 0);
}

void MyLCD::resetLineAfterPosition(int pos, int line) {
    internLCD->setCursor(pos, line);
    char lineChar[NBCOL - pos];
    lineChar[(NBCOL - pos) -1] = '\0';
    memset(lineChar, ' ', (NBCOL - pos) -1);
    internLCD->printstr(lineChar);
}

void MyLCD::clearAllScreen() { internLCD->clear(); }

MyLCD::~MyLCD() { delete internLCD; }