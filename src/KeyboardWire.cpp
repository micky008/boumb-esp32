#include "KeyboardWire.hpp"

void KeyboardWire::init() {
    Wire1.begin(19, 18);
    Wire1.beginTransmission(MODULE_ADDRESS);
    if (Wire1.endTransmission() != 0) {
        if (!Serial.available()) {
            Serial.begin(115200);
        }
        Serial.print(F("Le module PCF8574 ne répond pas à l'adresse 0x"));
        Serial.println(MODULE_ADDRESS, HEX);
        Serial.println(F("Arrêt du programme."));
    }
    fullReset();
}

void KeyboardWire::scan() {
    if (etat == KEYBOARD_STATE::ENTER_PRESSED) {
        return;
    }
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
                    etat = KEYBOARD_STATE::ENTER_PRESSED;
                    continue;
                } else if (mychar == 'C') {
                    kbBufferCode.remove(kbBufferCode.length() - 1);
                    etat = KEYBOARD_STATE::DELETE_PRESSED;
                } else {
                    kbBufferCode += mychar;
                }
            }
            if (oldx == x && (millis() - lastDebonce) >= DEBOUNCE) {
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