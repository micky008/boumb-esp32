#include <Arduino.h>

#include "Bornier.hpp"
#include "Choice.hpp"
#include "Configuration.hpp"
#include "Keyboard.hpp"
#include "LCD.hpp"
#include "Options.hpp"

#define VERSION 2.0

#define BORNIER_ETAT_ALL_FILS_OK 0
#define BORNIER_ETAT_WRONG_FIL 1
#define BORNIER_ETAT_GOOD_FIL 2

Options options;
MyLCD lcd;
Bornier bornier;

int bornierEtat = BORNIER_ETAT_ALL_FILS_OK;

TaskHandle_t Task1;

void core0(void *parameter);

void setup() {
    Serial1.begin(9600);
    lcd.initLCD();
    Keyboard::resetKeyboardState();
    xTaskCreatePinnedToCore(core0, "Task1", 10000, NULL, 0, &Task1, 0);
    bornier.init();
    Choice c(lcd);
    bool runPlay = false;
    while (!runPlay) {
        String res = c.theChoice("Jouer ?", "1-oui 2-non: ");
        if (res.equals("2")) {
            Configuration conf(options);
            conf.run();
        } else {
            runPlay = true;
        }
    }
}

void loop() {}

void core0(void *parameter) {
    int pos = 0;
    while (true) {
        if (!Keyboard::isKbBufferHaveEnterPressed) {
            int mychar = Serial1.read();
            if (mychar == -1) {
                continue;
            }
            if (mychar == 'E') {
                Keyboard::isKbBufferHaveEnterPressed = true;
                Serial1.write('o');
                continue;
            } else if (mychar == 'C' && pos > 0) {
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
        if (bornier.isCut()) {
            if (bornier.isGoodFil()) {
                bornierEtat = BORNIER_ETAT_GOOD_FIL;
            } else {
                bornierEtat = BORNIER_ETAT_WRONG_FIL;
            }
            return;
        }
    }
}