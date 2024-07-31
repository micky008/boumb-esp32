#include "Keyboard.hpp"

bool Keyboard::isKbBufferHaveEnterPressed = false;
bool Keyboard::isKbCorrectionPresed = false;
String Keyboard::kbBufferCode = "";

void Keyboard::resetKeyboardState() {
    Keyboard::isKbBufferHaveEnterPressed = false;
    Keyboard::isKbCorrectionPresed = false;
    Keyboard::kbBufferCode = "";
}