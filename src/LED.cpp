#include "LED.hpp"

MyLED::MyLED() {
    pixels = new Adafruit_NeoPixel(6, 17, NEO_GRB + NEO_KHZ800);
}

MyLED::~MyLED() { delete pixels; }