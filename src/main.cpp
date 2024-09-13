#include <Arduino.h>

#include "Bornier.hpp"
#include "Choice.hpp"
#include "Configuration.hpp"
#include "ConfigurationDebug.hpp"
// #include "KeyboardSerial.hpp"
// #include "KeyboardLibPCF8574.hpp"
#include "KeyboardWire.hpp"
#include "LCD.hpp"
#include "LED.hpp"
#include "Options.hpp"

MyLCD lcd;
Bornier bornier;
Options options;
// KeyboardLibPCF8574 keyboard; /idem que Wire mais en lib (utilise Wire)
// KeyboardSerial keyboard; //surtout utiliser pour le debug
KeyboardWire keyboard;  // comme LPCF8574 mais en utilisant Wire1
MyLED led;

int restant_time = 0;     // in millis
int diminue_time = 1000;  // in millis =>  1s
bool runPlay = false;
int maxTryRestant = 3;
unsigned long lastLoop = 0;

TaskHandle_t Task1 = NULL;

void core0(void* parameter);

void BOOM(bool restart = true) {
    // BOOM
    // declancher petard
    led.forceColor(LED_COLOR::RED);
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    if (restart) {
        ESP.restart();
    }
}

void setup() {
    initArduino();
    options.init();
    keyboard.init();
    lcd.init();
    led.init();
    bornier.init();
    xTaskCreatePinnedToCore(core0, "core0", 10000, NULL, 0, &Task1, 0);
    Choice c(lcd, keyboard);
    while (!runPlay) {
        String res = c.theChoice("Jouer ?", "1-oui 2-non: ");
        if (res.equals("2")) {
            Configuration conf(lcd, keyboard, options);
            conf.run();
        } else if (res.equals("99")) {
            ConfigurationDebug conf(lcd, keyboard, options);
            conf.run();
        } else {
            runPlay = true;
        }
    }
    lcd.applyOption(options);
    bornier.applyOption(options);
    led.applyOption(options);

    lcd.clearAllScreen();
    restant_time = options.getInitialTime();
    maxTryRestant = options.getMaxTry();
}

char temps[NBCOL];

void loop() {
    if ((millis() - lastLoop) >= diminue_time) {
        lastLoop = millis();
        led.on(restant_time);
        memset(temps, '\0', NBCOL - 1);
        int x = restant_time / 1000;
        int seconds = x % 60;
        x /= 60;
        int minutes = x % 60;
        x /= 60;
        int hours = x % 24;
        sprintf(temps, "Temps: %02d:%02d:%02d", hours, minutes, seconds);
        lcd.affiche(String(temps), LCD_LINE_UP);
    }
    if (restant_time <= 0) {
        lcd.affiche(String("Temps: 00:00:00"), LCD_LINE_UP); //enleve un bug graphique
        BOOM();
        return;
    }
    if (bornier.getEtat() != BORNIER_ETAT::ALL_FILS_OK) {
        Choice c(lcd, keyboard);
        if (bornier.getEtat() == BORNIER_ETAT::GOOD_FIL) {
            c.theChoice("BOMBE Desactivee", "press E");
            c.theChoice("remettre fil plz", "press to restart");
            ESP.restart();
        } else {
            BOOM(false);
            c.theChoice("remettre fil plz", "press to restart");
            ESP.restart();
        }
    }
    String codeLine = "Code : ";
    if (!keyboard.getContent().isEmpty()) {
        for (int i = 0; i < keyboard.getContent().length(); i++) {
            codeLine += "*";
        }
    }

    lcd.affiche(codeLine, LCD_LINE_DOWN);
    if (maxTryRestant == 0) {
        BOOM();
    }
    if (keyboard.etat == KEYBOARD_STATE::ENTER_PRESSED) {
        String readCode = keyboard.lire();
        if (readCode.equals(options.getCode())) {
            Choice c(lcd, keyboard);
            c.theChoice("BOMBE Desactivee", "press to restart");
            ESP.restart();
        } else {
            maxTryRestant--;
            diminue_time = (1000 * maxTryRestant) / options.getMaxTry();
            lcd.resetLine(LCD_LINE_DOWN);
        }
    }
    if (keyboard.etat == KEYBOARD_STATE::DELETE_PRESSED) {
        // delete toute la ligne car elle serra re-ecrite a la prochaine
        // iteration
        lcd.resetLine(LCD_LINE_DOWN);
        keyboard.resetStateOnly();
    }
    led.off();
}

void core0(void* parameter) {
    unsigned long last = 0;
    while (true) {
        if (runPlay) {
            if ((millis() - last) >= diminue_time) {
                last = millis();
                restant_time -= 1000;
                if (restant_time <= 0) {
                    restant_time = 0;
                }
            }
        }
        bornier.scan();
        keyboard.scan();
    }
    vTaskDelete(Task1);
}