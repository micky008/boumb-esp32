#ifndef _MY_LED__
#define _MY_LED__

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define NB_LED 6
#define NO_LED -1

class MyLED {
   public:
    MyLED();
    ~MyLED();
    void on(int restantTime);
    void off();
    void setInitialTime(int initialTime);
   private:
    int initialTime;
    Adafruit_NeoPixel *pixels;
    int doublePeriode;
    int periode;
    uint32_t green;
    uint32_t orenge;
    uint32_t red;
    bool isOn;

};

#endif