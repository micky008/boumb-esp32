#ifndef __OPTIONMAXTIME_H__
#define __OPTIONMAXTIME_H__

#include <Arduino.h>

class OptionMaxTime {
   public:
    virtual uint16_t getMaxTimeInMin() = 0;
    virtual void setMaxTimeInMin(uint16_t maxTime) = 0;
};

#endif