#ifndef _MY_CONFDEBUG__
#define _MY_CONFDEBUG__

#include "Configuration.hpp"

class ConfigurationDebug : Configuration {
   public:
    ConfigurationDebug(MyLCD &lcd, Options &opts);
    bool run();
};

#endif