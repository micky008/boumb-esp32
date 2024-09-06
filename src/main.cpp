#include <Arduino.h>

#include "Bornier.hpp"
#include "Choice.hpp"
#include "Configuration.hpp"
#include "ConfigurationDebug.hpp"
#include "Keyboard.hpp"
#include "LCD.hpp"
#include "Options.hpp"

#define RXD2 16
#define TXD2 17

#define BORNIER_ETAT_ALL_FILS_OK 0
#define BORNIER_ETAT_WRONG_FIL 1
#define BORNIER_ETAT_GOOD_FIL 2

MyLCD lcd;
Bornier bornier;
Options options;
PCF8574 keyboardI2C(0x20);
Keyboard keyboard(keyboardI2C);

int bornierEtat = BORNIER_ETAT_ALL_FILS_OK;

int restant_time = 0;     // in millis
int diminue_time = 1000;  // in milli =>  1s
bool runPlay = false;
int maxTryRestant = 3;

TaskHandle_t Task1 = NULL;

void core0(void* parameter);

void BOOM(bool restart = true) {
    // BOOM
    // declancher petard
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    if (restart) {
        ESP.restart();
    }
}

void setup() {
    Serial.begin(115200);
    bornierEtat = BORNIER_ETAT_ALL_FILS_OK;
    lcd.initLCD();
    Keyboard::resetALLKeyboardState();
    xTaskCreatePinnedToCore(core0, "core0", 10000, NULL, 0, &Task1, 0);
    bornier.init();
    Choice c(lcd);
    while (!runPlay) {
        String res = c.theChoice("Jouer ?", "1-oui 2-non: ");
        if (res.equals("2")) {
            Configuration conf(lcd, options);
            conf.run();
        } else if (res.equals("99")) {
            ConfigurationDebug conf(lcd, options);
            conf.run();
        } else {
            runPlay = true;
        }
    }
    lcd.clearAllScreen();
    bornier.setFil(options.getFil());
    restant_time = options.getMaxTimeInMin() * 60000;
    maxTryRestant = options.getMaxTry();
}

char temps[NBCOL];

void loop() {
    memset(temps, 0, NBCOL);
    int x = restant_time / 1000;
    int seconds = x % 60;
    x /= 60;
    int minutes = x % 60;
    x /= 60;
    int hours = x % 24;
    sprintf(temps, "Temps: %02d:%02d:%02d", hours, minutes, seconds);
    lcd.affiche(String(temps), LCD_LINE_UP);

    if (restant_time <= 0) {
        BOOM();
        return;
    }
    if (bornierEtat != BORNIER_ETAT_ALL_FILS_OK) {
        Choice c(lcd);
        if (bornierEtat == BORNIER_ETAT_GOOD_FIL) {
            c.theChoice("BOMBE Desactivee", "press keyboard");
            c.theChoice("remettre fil plz", "press to restart");
            ESP.restart();
        } else {
            BOOM(false);
            c.theChoice("remettre fil plz", "press to restart");
            c.theChoice("noFil: ", String(bornier.getFil()));
            ESP.restart();
        }
    }
    String codeLine = "Code :";
    if (!Keyboard::kbBufferCode.isEmpty()) {
        for (int i = 0; i < Keyboard::kbBufferCode.length(); i++) {
            codeLine += "*";
        }
    }

    lcd.affiche(codeLine, LCD_LINE_DOWN);
    if (maxTryRestant == 0) {
        BOOM();
    }
    if (Keyboard::isKbBufferHaveEnterPressed) {
        if (Keyboard::kbBufferCode.equals(options.getCode())) {
            Choice c(lcd);
            c.theChoice("BOMBE Desactivee", "press to restart");
            ESP.restart();
        } else {
            maxTryRestant--;
            diminue_time = (1000 * maxTryRestant) / options.getMaxTry();
            Keyboard::resetALLKeyboardState();
            lcd.resetLine(LCD_LINE_DOWN);
        }
    }
    if (Keyboard::isKbCorrectionPresed) {
        lcd.resetLine(LCD_LINE_DOWN);
        Keyboard::resetCorrectionKeyboardState();
    }
    delayMicroseconds(diminue_time);
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
        if (bornierEtat == BORNIER_ETAT_ALL_FILS_OK && bornier.isCut()) {
            if (bornier.isGoodFil()) {
                bornierEtat = BORNIER_ETAT_GOOD_FIL;
            } else {
                bornierEtat = BORNIER_ETAT_WRONG_FIL;
            }
        }
        if (!Keyboard::isKbBufferHaveEnterPressed) {
            keyboard.lire();
        }
    }
    vTaskDelete(Task1);
}