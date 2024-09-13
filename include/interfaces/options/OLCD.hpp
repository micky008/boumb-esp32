#ifndef __OPTIONLCD_H__
#define __OPTIONLCD_H__

class OptionLCD {
   public:
    virtual bool getBrigtnessOn() = 0;
    virtual void setBrignessOn(bool onOff) = 0;
};

#endif