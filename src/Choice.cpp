#include "Choice.hpp"



Choice::Choice(MyLCD& lcd) : lcd(lcd) {}

String Choice::theChoice(String lineUp, String lineDown) {
    Keyboard::resetALLKeyboardState();
    lcd.affiche(lineUp, LCD_LINE_UP);
    lcd.affiche(lineDown, LCD_LINE_DOWN);
    int pos = strlen(lineDown.c_str());
    int originalPos = pos;
    while (!Keyboard::isKbBufferHaveEnterPressed) {
        if (Keyboard::isKbCorrectionPresed) {
            pos--;
            if (pos <= originalPos) {
                pos = originalPos;
            }
            lcd.resetLineAfterPosition(pos, LCD_LINE_DOWN);
            Keyboard::resetCorrectionKeyboardState();
        }
        lcd.append(Keyboard::kbBufferCode, pos, LCD_LINE_DOWN);
    }
    String res = Keyboard::kbBufferCode;
    Keyboard::resetALLKeyboardState();
    return res;
}