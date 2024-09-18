#ifndef _MY_OPTIONS__
#define _MY_OPTIONS__

#include <Arduino.h>
#include <Preferences.h>

#include "interfaces/Initialisation.hpp"
#include "interfaces/options/OBornier.hpp"
#include "interfaces/options/OCode.hpp"
#include "interfaces/options/OLCD.hpp"
#include "interfaces/options/OLED.hpp"
#include "interfaces/options/OMaxTime.hpp"
#include "interfaces/options/OMaxTry.hpp"

#define VERSION 2.1

#define OPT_MAX_TIME "maxtime"
#define OPT_CODE "optcode"
#define OPT_MAX_TRY "maxtry"
#define OPT_FIL_BORNIER "nofilbornier"
#define OPT_BRIGNESS "bonoff"
#define OPT_LED_ON_OFF "ledonoff"
#define OPT_NO_FIL "nofil"

class Options : Initialisation,
                public OptionBornier,
                public OptionCode,
                public OptionLCD,
                public OptionLED,
                public OptionMaxTime,
                public OptionMaxTry {
   public:
    void init();
    void saveAllOptions();

    FIL_BORNIER getFil();
    void setFil(FIL_BORNIER fil);
    String getCode();
    void setCode(String code);
    bool getBrigtnessOn();
    void setBrignessOn(bool onOff);
    bool isLEDOn();
    void setLedOn(bool onOff);
    int getInitialTime();
    uint16_t getMaxTimeInMin();
    void setMaxTimeInMin(uint16_t maxtime);
    uint8_t getMaxTry();
    void setMaxTry(uint8_t maxTry);

   private:
    Preferences *opts;
    int maxTimeInMin = 60;
    String code = "123456";
    int maxTry = 3;
    bool brignessOnOff = true;
    int fil = 2;
    bool ledOn = true;
};

#endif