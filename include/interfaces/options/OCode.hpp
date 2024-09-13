#ifndef __OPTIONCODE_H__
#define __OPTIONCODE_H__

#include <Arduino.h>

class OptionCode {

    public :
        virtual String getCode() = 0;
        virtual void setCode(String code) = 0;
};

#endif