#include "Choice.hpp"

Choice::Choice(MyLCD& lcd, Keyboard& keyboard) : lcd(lcd), kb(keyboard) {}

String Choice::theChoice(String lineUp, String lineDown) {
    lcd.clearAllScreen();
    kb.fullReset();
    lcd.affiche(lineUp, LCD_LINE_UP);
    lcd.affiche(lineDown, LCD_LINE_DOWN);
    int pos = strlen(lineDown.c_str());
    int originalPos = pos;
    String res = "";
    while (kb.etat != KEYBOARD_STATE::ENTER_PRESSED) {
        if (kb.etat == KEYBOARD_STATE::DELETE_PRESSED) {
            pos--;
            if (pos <= originalPos) {
                pos = originalPos;
            }
            lcd.resetLineAfterPosition(pos, LCD_LINE_DOWN);
            kb.resetStateOnly();
        }
        if (res.equals(kb.getContent())) {
            lcd.append(kb.getContent(), pos, LCD_LINE_DOWN);
            res = kb.getContent();
        }
    }
    return kb.lire();
}