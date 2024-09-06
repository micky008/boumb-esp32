#include "Keyboard.hpp"

bool Keyboard::isKbBufferHaveEnterPressed = false;
bool Keyboard::isKbCorrectionPresed = false;
String Keyboard::kbBufferCode = "";

void Keyboard::resetALLKeyboardState() {
    Keyboard::isKbBufferHaveEnterPressed = false;
    Keyboard::isKbCorrectionPresed = false;
    Keyboard::kbBufferCode = "";
}

void Keyboard::resetCorrectionKeyboardState() {
    Keyboard::isKbCorrectionPresed = false;
}

Keyboard::Keyboard( PCF8574 &keyboardI2C) : keyboardI2C(keyboardI2C){
    keyboardI2C.pinMode(P0, OUTPUT);
    keyboardI2C.pinMode(P1, OUTPUT); 
    keyboardI2C.pinMode(P2, OUTPUT);
    keyboardI2C.pinMode(P3, OUTPUT);
    keyboardI2C.pinMode(P4, INPUT);
    keyboardI2C.pinMode(P5, INPUT);
    keyboardI2C.pinMode(P6, INPUT);
    keyboardI2C.pinMode(P7, INPUT);
}

void Keyboard::lire() {
    for (int x = 0; x < 4; x++) {
        keyboardI2C.digitalWrite(x, HIGH);
        for (int y = 4; y < 8; y++) {
            if (keyboardI2C.digitalRead(y) == 0) {
                continue;
            }
            char mychar = matrice[x][y];
            if (rebond != mychar) {
                rebond = mychar;
            }else {
                continue;
            }
            if (mychar == 'E') {
                Keyboard::isKbBufferHaveEnterPressed = true;
                return;
            } else if (mychar == 'C') {
                Keyboard::kbBufferCode.remove(Keyboard::kbBufferCode.length() - 1);
                Keyboard::isKbCorrectionPresed = true;
            } else {
                Keyboard::kbBufferCode += mychar;
            }
        }
        keyboardI2C.digitalWrite(x, LOW);
    }
}
