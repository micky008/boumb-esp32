#include <Arduino.h>

#include "Bornier.hpp"
#include "Choice.hpp"
#include "Configuration.hpp"
#include "Keyboard.hpp"
#include "LCD.hpp"
#include "Options.hpp"

#define BORNIER_ETAT_ALL_FILS_OK 0
#define BORNIER_ETAT_WRONG_FIL 1
#define BORNIER_ETAT_GOOD_FIL 2

Options options;
MyLCD lcd;
Bornier bornier;

int bornierEtat = BORNIER_ETAT_ALL_FILS_OK;

int restant_time = 0; //in millis
int diminue_time = 1000; //in milli =>  1s
bool runPlay = false;
int maxTryRestant;

TaskHandle_t Task1;

void core0(void* parameter);

void BOOM() {
    //BOOM 
    //declancher petard
    ESP.restart();
}


void setup() {
    bornierEtat = BORNIER_ETAT_ALL_FILS_OK;
    Serial1.begin(9600);
    lcd.initLCD();
    Keyboard::resetKeyboardState();
    xTaskCreatePinnedToCore(core0, "Task1", 10000, NULL, 0, &Task1, 0);
    bornier.init();
    Choice c(lcd);
    while (!runPlay) {
        String res = c.theChoice("Jouer ?", "1-oui 2-non: ");
        if (res.equals("2")) {
            Configuration conf(lcd, options);
            conf.run();
        }
        else {
            runPlay = true;
        }
    }
    restant_time = options.getMaxTimeInMin() * 60000;
    maxTryRestant = options.getMaxTry();
}

void loop() {
    int x = restant_time / 1000;
    int seconds = x % 60;
    x /= 60;
    int minutes = x % 60;
    x /= 60;
    int hours = x % 24;
    String h = hours < 10 ? "0" + hours : "" + hours;
    String min = minutes < 10 ? "0" + minutes : "" + minutes;
    String sec = seconds < 10 ? "0" + seconds : "" + seconds;
    lcd.affiche("Temps: " + h + ":" + min + ":" + sec, LCD_LINE_UP);

    if (restant_time <= 0) {
        BOOM();
        return;
    }
    if (bornierEtat != BORNIER_ETAT_ALL_FILS_OK) {
        if (bornierEtat == BORNIER_ETAT_GOOD_FIL) {
            Choice c(lcd);
            c.theChoice("BOMBE Desactivee", "press keyboard");
            c.theChoice("remettre fil plz", "press to restart");
            ESP.restart();
        }
        else {
            BOOM();
        }
    }
    String codeLine = "Code:";
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
        }
        else {
            maxTryRestant--;
        }
    }
    delayMicroseconds(diminue_time);
}

void core0(void* parameter) {
    int pos = 0;
    unsigned long last = 0;
    while (true) {
        if (runPlay) {
            if ((millis() - last) >= diminue_time) {
                last = millis();
                restant_time -= diminue_time;
                if (restant_time <= 0) {
                    restant_time = 0;
                }
            }
        }
        if (bornierEtat == BORNIER_ETAT_ALL_FILS_OK && bornier.isCut()) {
            if (bornier.isGoodFil()) {
                bornierEtat = BORNIER_ETAT_GOOD_FIL;
            }
            else {
                bornierEtat = BORNIER_ETAT_WRONG_FIL;
            }
            return;
        }
        if (!Keyboard::isKbBufferHaveEnterPressed) {
            int mychar = Serial1.read();
            if (mychar == -1) {
                continue;
            }
            if (mychar == 'E') {
                Keyboard::isKbBufferHaveEnterPressed = true;
                Serial1.write('o');
                continue;
            }
            else if (mychar == 'C' && pos > 0) {
                Keyboard::kbBufferCode.remove(pos);
                Keyboard::isKbCorrectionPresed = true;
                --pos;
                Serial1.write('o');
                continue;
            }
            pos++;
            Serial1.write('o');
            Keyboard::kbBufferCode += (char)mychar;
        }
    }
}