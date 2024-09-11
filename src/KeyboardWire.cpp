#include "KeyboardWire.hpp"

void KeyboardWire::init() {
    Wire1.begin(19, 18);
    Wire1.beginTransmission(MODULE_ADDRESS);
    if (Wire1.endTransmission() != 0) {
        Serial.print(F("Le module PCF8574 ne répond pas à l'adresse 0x"));
        Serial.println(MODULE_ADDRESS, HEX);
        Serial.println(F("Arrêt du programme."));
    }
    Keyboard::resetALLKeyboardState();
}

void KeyboardWire::lire() {
    for (int y = 0; y < 4; y++) {
        Wire1.beginTransmission(MODULE_ADDRESS);
        Wire1.write(row[y]);
        Wire1.endTransmission();
        for (int x = 4; x < 8; x++) {
            if (digitalRead(x)) {
                char mychar = matrice[y][x - 4];
                if (mychar == rebond) {
                    continue;
                }
                rebond = mychar;
                oldx = x;
                if (mychar == 'E') {
                    Keyboard::isKbBufferHaveEnterPressed = true;
                    continue;
                } else if (mychar == 'C') {
                    Keyboard::kbBufferCode.remove(
                        Keyboard::kbBufferCode.length() - 1);
                    Keyboard::isKbCorrectionPresed = true;
                } else {
                    Keyboard::kbBufferCode += mychar;
                }
            }
            if (oldx == x && (millis() - lastDebonce) >= DEBOUNCE  ) {
                rebond = 0;
                lastDebonce = millis();
            }
        }
    }
}

bool KeyboardWire::digitalRead(int pin) {
    Wire1.requestFrom(MODULE_ADDRESS, 1);
    Wire1.beginTransmission(MODULE_ADDRESS);
    byte response = Wire1.read();
    Wire1.endTransmission();
    return ((response >> pin) & 0b00000001) == 0;
}