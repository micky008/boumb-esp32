#include "Choice.hpp"



Choice::Choice(MyLCD& lcd) : lcd(lcd) {}

String Choice::theChoice(String lineUp, String lineDown) {
    lcd.affiche(lineUp, LCD_LINE_UP);
    lcd.affiche(lineDown, LCD_LINE_DOWN);
    int pos = strlen(lineDown.c_str());
    while (!Keyboard::isKbBufferHaveEnterPressed) {
        if (Keyboard::isKbCorrectionPresed) {
            pos--;
        }
        lcd.append(Keyboard::kbBufferCode, pos, LCD_LINE_DOWN);
    }
    String res = Keyboard::kbBufferCode;
    Keyboard::resetKeyboardState();
    return res;
}