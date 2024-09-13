#ifndef __OPTIONLED_H__
#define __OPTIONLED_H__

class OptionLED {
   public:
    virtual bool isLEDOn() = 0;
    virtual void setLedOn(bool onOff) = 0;
    virtual int getInitialTime() = 0;
};

#endif