#ifndef _MY_CONF__
#define _MY_CONF__

#include <Arduino.h>

#include "Choice.hpp"
#include "Options.hpp"

class Configuration {
   public:
    Configuration(MyLCD &lcd, Keyboard& kb,Options &opts);
    bool run();

   protected:
    MyLCD &lcd;
    Keyboard& kb;
    Options &options;
};

#endif