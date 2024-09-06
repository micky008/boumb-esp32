#include "LED.hpp"

MyLED::MyLED() {    
    pixels = new Adafruit_NeoPixel(NB_LED, 17, NEO_GRB + NEO_KHZ800);
    pixels->begin();
    green = pixels->Color(0, 255, 0);
    orenge = pixels->Color(255, 79, 0);
    red = pixels->Color(255, 0, 0);
}

void MyLED::on(int restantTime) {
    for (int i = 0; i < NB_LED; i++) {
        if (restantTime > doublePeriode) {
            // vert
            pixels->setPixelColor(i, green);
        } else if (restantTime > periode && restantTime < doublePeriode) {
            // orenge FF4F00
            pixels->setPixelColor(i, orenge);
        } else {
            // red
            pixels->setPixelColor(i, red);
        }
    }
    pixels->show();
}

void MyLED::off() {
    pixels->clear();
    pixels->show();
}

void MyLED::setInitialTime(int initialTime){
    this->initialTime = initialTime;
    periode = initialTime / 3;
    doublePeriode = periode * 2;
}

MyLED::~MyLED() { delete pixels; }