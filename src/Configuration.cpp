#include "Configuration.hpp"

Configuration::Configuration(MyLCD& lcd, Keyboard& kb, Options& opts)
    : lcd(lcd), kb(kb), options(opts) {}

bool Configuration::run() {
    lcd.clearAllScreen();
    Choice firstEcran(lcd, kb);
    String res = firstEcran.theChoice("Num. options", "(1-7) : ");
    if (res.equals("1")) {
        res = firstEcran.theChoice("Max time", "(in min): ");
        options.setMaxTimeInMin(res.toInt());
    } else if (res.equals("2")) {
        res = firstEcran.theChoice("Code-6char.max:", "");
        options.setCode(res);
    } else if (res.equals("3")) {
        res = firstEcran.theChoice("Max. essais:", "");
        if (res.indexOf("A") > -1 || res.indexOf("B") > -1 ||
            res.indexOf("C") > -1 || res.indexOf("F") > -1) {
            lcd.append("PAS DE LETTRE!", 0, LCD_LINE_DOWN);
            delay(3000);
            return true;
        }
        options.setMaxTry(res.toInt());
    } else if (res.equals("4")) {
        lcd.clearAllScreen();
        lcd.affiche("VERSION: ", LCD_LINE_UP);
        String ver = "";
        ver += VERSION;
        lcd.affiche(ver, LCD_LINE_DOWN);
        delay(3000);
    } else if (res.equals("5")) {
        res = firstEcran.theChoice("Brightness ?", "1-On/2-off: ");
        options.setBrignessOn(res.equals("1"));
        lcd.applyOption(options);
    } else if (res.equals("6")) {
        res = firstEcran.theChoice("LED ?", "1-On/2-off: ");
        options.setLedOn(res.equals("1"));
    } else if (res.equals("7")) {
        res = firstEcran.theChoice("no FIL (1-4)?", "");
        int toint = -1;
        if (res.charAt(0) == 'A') {
            toint = -1;
        } else {
            toint = res.toInt();
            if (toint < 1 && toint > 4) {
                lcd.affiche("JUSTE 1-4-A!", LCD_LINE_DOWN);
                delay(3000);
                return true;
            }
        }
        options.setFil(static_cast<FIL_BORNIER>(toint));
    } else {
        return false;
    }
    options.saveAllOptions();
    return true;
}