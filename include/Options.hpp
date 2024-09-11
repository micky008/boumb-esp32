#ifndef _MY_OPTIONS__
#define _MY_OPTIONS__

#include <Arduino.h>
#include <Preferences.h>

#define VERSION 2.0

#define OPT_MAX_TIME "maxtime"
#define OPT_CODE "optcode"
#define OPT_MAX_TRY "maxtry"
#define OPT_FIL_BORNIER "nofilbornier"
#define OPT_BRIGNESS "bonoff"
#define OPT_LED_ON_OFF "ledonoff"
#define OPT_NO_FIL "nofil"

class Options {
   public:
    Options();
    ~Options();
    void initOptions();
    void saveAllOptions();
    void setMaxTime(int maxtime);
    void setCode(String code);
    void setMaxTry(int maxtry);
    void setBrigness(bool on);
    void setFil(int file);
    void setLedStatus(bool on);

    int getMaxTimeInMin();
    String getCode();
    int getMaxTry();
    int getFil();
    bool getLedStatus();
    bool getBrigntnessStatus();



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