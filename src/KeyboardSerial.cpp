#include "KeyboardSerial.hpp"

void KeyboardSerial::init() {

}

void KeyboardSerial::lire() {
    int mychar = Serial.read();
    if (mychar == -1) {
        return;
    }
    if ((char)mychar == 'E') {
        Keyboard::isKbBufferHaveEnterPressed = true;
        return;
    }
    else if ((char)mychar == 'C') {
        if (Keyboard::kbBufferCode.isEmpty()) {
            return;
        }
        Keyboard::kbBufferCode.remove(Keyboard::kbBufferCode.length() - 1);
        Keyboard::isKbCorrectionPresed = true;
        return;
    }
    Keyboard::kbBufferCode += (char)mychar;
}
