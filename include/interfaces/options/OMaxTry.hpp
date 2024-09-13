#ifndef __OPTIONMAXTRY_H__
#define __OPTIONMAXTRY_H__

#include <Arduino.h>

class OptionMaxTry {


    public :
        virtual uint8_t getMaxTry() = 0;
        virtual void setMaxTry(uint8_t maxTry) = 0;
};

#endif