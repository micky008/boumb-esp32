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
KeyboardWire keyboard; //comme LPCF8574 mais en utilisant Wire1
MyLED led;

int restant_time = 0;     // in millis
int diminue_time = 1000;  // in millis =>  1s
bool runPlay = false;
int maxTryRestant = 3;

TaskHandle_t Task1 = NULL;

void core0(void* parameter);

void BOOM(bool restart = true) {
    // BOOM
    // declancher petard
    led.off();
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    if (restart) {
        ESP.restart();
    }
}

void setup() {
    initArduino();
    //Serial.begin(115200);
    options.init();
    keyboard.init();
    lcd.init();
    led.init();
    bornier.init();
    xTaskCreatePinnedToCore(core0, "core0", 10000, NULL, 0, &Task1, 0);
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
    lcd.applyOption(options);
    bornier.applyOption(options);
    led.applyOption(options);
    
    lcd.clearAllScreen();
    restant_time = options.getInitialTime();
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
    if (bornier.getEtat() != BORNIER_ETAT::ALL_FILS_OK) {
        Choice c(lcd);
        if (bornier.getEtat() == BORNIER_ETAT::GOOD_FIL) {
            c.theChoice("BOMBE Desactivee", "press keyboard");
            c.theChoice("remettre fil plz", "press to restart");
            ESP.restart();
        } else {
            BOOM(false);
            c.theChoice("remettre fil plz", "press to restart");
            ESP.restart();
        }
    }
    String codeLine = "Code : ";
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
    led.off();
    delay(diminue_time);
    led.on(restant_time);    
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
        bornier.lire();
        keyboard.lire();
    }
    vTaskDelete(Task1);
}