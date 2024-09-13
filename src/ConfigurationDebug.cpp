#include "ConfigurationDebug.hpp"

ConfigurationDebug::ConfigurationDebug(MyLCD &lcd, Keyboard& kb,Options &opts)
    : Configuration(lcd, kb, opts) {}

bool ConfigurationDebug::run() {
    lcd.clearAllScreen();
    Choice firstEcran(lcd, kb);
    String res = firstEcran.theChoice("Num. options", "(1-7) : ");
    if (res.equals("1")) {
        firstEcran.theChoice("Max time Debug",
                             String(options.getMaxTimeInMin()));
    } else if (res.equals("2")) {
        firstEcran.theChoice("Code Debug", options.getCode());
    } else if (res.equals("3")) {
        firstEcran.theChoice("Max. try Debug", String(options.getMaxTry()));
    } else if (res.equals("4")) {
        lcd.clearAllScreen();
        lcd.affiche("VERSION: ", LCD_LINE_UP);
        lcd.affiche(String(VERSION), LCD_LINE_DOWN);
    } else if (res.equals("5")) {
        firstEcran.theChoice("Brightness ?", "lol");
    } else if (res.equals("6")) {
        res = firstEcran.theChoice(
            "LED ? Debug", String(options.isLEDOn() ? "true" : "false"));
    } else if (res.equals("7")) {
        firstEcran.theChoice("no FIL debug", String(options.getFil()));
    } else {
        return false;
    }
    return true;
}