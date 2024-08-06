#ifndef _MY_LED__
#define _MY_LED__

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

class MyLED {
   public:
    MyLED();
    ~MyLED();

   private:
    Adafruit_NeoPixel *pixels;
};

#endif