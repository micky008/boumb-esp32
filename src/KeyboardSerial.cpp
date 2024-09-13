#include "KeyboardSerial.hpp"

void KeyboardSerial::init() {
    Serial.begin(115200);
}

void KeyboardSerial::scan() {
    int mychar = Serial.read();
    if (mychar == -1) {
        return;
    }
    if ((char)mychar == 'E') {
        Keyboard::etat = KEYBOARD_STATE::ENTER_PRESSED;        
        return;
    }
    else if ((char)mychar == 'C') {
        if (kbBufferCode.isEmpty()) {
            return;
        }
        kbBufferCode.remove(kbBufferCode.length() - 1);
        Keyboard::etat = KEYBOARD_STATE::DELETE_PRESSED;
        return;
    }
    kbBufferCode += (char)mychar;
}
