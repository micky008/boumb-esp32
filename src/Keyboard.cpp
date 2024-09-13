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
