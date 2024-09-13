#ifndef _MY_CONFDEBUG__
#define _MY_CONFDEBUG__

#include "Configuration.hpp"

class ConfigurationDebug : Configuration {
   public:
    ConfigurationDebug(MyLCD &lcd, Keyboard &kb, Options &opts);
    bool run();
};

#endif