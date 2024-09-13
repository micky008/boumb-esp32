#include "Keyboard.hpp"

String Keyboard::lire() {
    String res = kbBufferCode;
    fullReset();
    return res;
}

void Keyboard::fullReset() {
    Keyboard::etat = KEYBOARD_STATE::IDLE;
    kbBufferCode = "";
}

void Keyboard::resetStateOnly() { Keyboard::etat = KEYBOARD_STATE::IDLE; }

String Keyboard::getContent() { return kbBufferCode; }