#include "KeyboardLibPCF8574.hpp"

KeyboardLibPCF8574::KeyboardLibPCF8574() { keyboardI2C = new PCF8574(0x20); }

KeyboardLibPCF8574::~KeyboardLibPCF8574() { delete keyboardI2C; }

void KeyboardLibPCF8574::init() {
    keyboardI2C = new PCF8574(0x20);
    keyboardI2C->pinMode(P0, OUTPUT);
    keyboardI2C->pinMode(P1, OUTPUT);
    keyboardI2C->pinMode(P2, OUTPUT);
    keyboardI2C->pinMode(P3, OUTPUT);
    keyboardI2C->pinMode(P4, INPUT);
    keyboardI2C->pinMode(P5, INPUT);
    keyboardI2C->pinMode(P6, INPUT);
    keyboardI2C->pinMode(P7, INPUT);
    keyboardI2C->begin();
}

void KeyboardLibPCF8574::scan() {
    if (Keyboard::etat == KEYBOARD_STATE::ENTER_PRESSED) {
        return;
    }
    for (int x = 0; x < 4; x++) {
        keyboardI2C->digitalWrite(x, HIGH);
        for (int y = 4; y < 8; y++) {
            if (keyboardI2C->digitalRead(y) == 0) {
                continue;
            }
            char mychar = matrice[x][y];
            if (rebond != mychar) {
                rebond = mychar;
            } else {
                continue;
            }
            if (mychar == 'E') {
                Keyboard::etat = KEYBOARD_STATE::ENTER_PRESSED;
                return;
            } else if (mychar == 'C') {
                kbBufferCode.remove(kbBufferCode.length() - 1);
                Keyboard::etat = KEYBOARD_STATE::DELETE_PRESSED;
            } else {
                kbBufferCode += mychar;
            }
        }
        keyboardI2C->digitalWrite(x, LOW);
    }
}
