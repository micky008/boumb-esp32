#include <Arduino.h>

#include "Bornier.hpp"
#include "Choice.hpp"
#include "Configuration.hpp"
#include "Keyboard.hpp"
#include "LCD.hpp"
#include "Options.hpp"
#include <HardwareSerial.h>

#define RXD2 16
#define TXD2 17

#define BORNIER_ETAT_ALL_FILS_OK 0
#define BORNIER_ETAT_WRONG_FIL 1
#define BORNIER_ETAT_GOOD_FIL 2

HardwareSerial MySerial(1);

//Options options;
MyLCD lcd;
Bornier bornier;

int bornierEtat = BORNIER_ETAT_ALL_FILS_OK;

int restant_time = 0; //in millis
int diminue_time = 1000; //in milli =>  1s
bool runPlay = false;
int maxTryRestant = 3;

TaskHandle_t Task1 = NULL;

void core0(void* parameter);

void BOOM() {
    //BOOM 
    //declancher petard
    digitalWrite(2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(2, LOW);
    ESP.restart();
}


void setup() {

    Serial.begin(115200);

    bornierEtat = BORNIER_ETAT_ALL_FILS_OK;
    MySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
    lcd.initLCD();
    Keyboard::resetALLKeyboardState();
    xTaskCreatePinnedToCore(core0, "core0", 10000, NULL, 0, &Task1, 0);
    bornier.init();
    Choice c(lcd);
    while (!runPlay) {
        String res = c.theChoice("Jouer ?", "1-oui 2-non: ");
        if (res.equals("2")) {
            //Configuration conf(lcd, NULL);//options);
            //conf.run();
        }
        else {
            runPlay = true;
        }
    }
    lcd.clearAllScreen();
    restant_time = 600000;
    // restant_time = options.getMaxTimeInMin() * 60000;
    // maxTryRestant = options.getMaxTry();
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
        //if (Keyboard::kbBufferCode.equals(options.getCode())) {
        if (Keyboard::kbBufferCode.equals("123456")) {
            Choice c(lcd);
            c.theChoice("BOMBE Desactivee", "press to restart");
            ESP.restart();
        }
        else {
            maxTryRestant--;
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
        // if (bornierEtat == BORNIER_ETAT_ALL_FILS_OK && bornier.isCut()) {
        //     if (bornier.isGoodFil()) {
        //         bornierEtat = BORNIER_ETAT_GOOD_FIL;
        //     }
        //     else {
        //         bornierEtat = BORNIER_ETAT_WRONG_FIL;
        //     }
        //     break;
        // }
        if (!Keyboard::isKbBufferHaveEnterPressed) {
            int mychar = MySerial.read();
            if (mychar == -1) {
                continue;
            }
            if ((char)mychar == 'E') {
                Keyboard::isKbBufferHaveEnterPressed = true;
                MySerial.write('o');
                continue;
            }
            else if ((char)mychar == 'C') {
                Keyboard::kbBufferCode.remove(pos - 1);
                Keyboard::isKbCorrectionPresed = true;
                --pos;
                if (pos == 0) {
                    Keyboard::kbBufferCode = "";
                }
                MySerial.write('o');
                continue;
            }
            MySerial.println((char)mychar);
            pos++;
            //MySerial.write('o');
            Keyboard::kbBufferCode += (char)mychar;
        }
    }
    vTaskDelete(Task1);
}