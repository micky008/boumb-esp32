#ifndef _MY_CONF__
#define _MY_CONF__

#include <Arduino.h>
#include "Options.hpp"

class Configuration {
    public:
        Configuration(Options &opts);
        bool run();

    private:
    
};


#endif