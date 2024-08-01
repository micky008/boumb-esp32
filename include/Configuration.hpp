#ifndef _MY_CONF__
#define _MY_CONF__

#include <Arduino.h>

#include "Choice.hpp"
#include "Options.hpp"

class Configuration {
   public:
    Configuration(MyLCD &lcd, Options &opts);
    bool run();

   private:
    Options &options;
    MyLCD &lcd;
};

#endif