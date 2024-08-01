#include "Configuration.hpp"

Configuration::Configuration(MyLCD &lcd, Options &opts)
    : lcd(lcd), options(opts) {}

bool Configuration::run() {
    Choice firstEcran(lcd);
    String res = firstEcran.theChoice("Num. options", "(1-6) : ");
    if (res.equals("1")) {
    } else if (res.equals("1")) {
        res = firstEcran.theChoice("Max time", "(in min): ");
        options.setMaxTime(res.toInt());
    } else if (res.equals("2")) {
        res = firstEcran.theChoice("Code-6char.max:", " ");
        options.setCode(res);
    } else if (res.equals("3")) {
        res = firstEcran.theChoice("Max. essais:", "");
        if (res.indexOf("A") > -1 || res.indexOf("B") > -1 ||
            res.indexOf("C") > -1 || res.indexOf("F") > -1) {
                lcd.append("PAS DE LETTRE!", 0, LINE_DOWN);
                delay(3000);
                return true;
            }
            options.setMaxTry(res.toInt());
    } else if (res.equals("4")) {
        lcd.affiche("VERSION: ", LINE_UP);
        String ver = "";
        ver += VERSION;
        lcd.affiche(ver, LINE_DOWN);
        delay(3000);
    } else if (res.equals("5")) {
        res = firstEcran.theChoice("Brightness ?", "1-On/2-off: ");
        if (res.equals("1")){
            lcd.setBrightnessOn(true);
        }else {
            lcd.setBrightnessOn(false);
        }
    } else {
        return false;
    }
    return true;
}