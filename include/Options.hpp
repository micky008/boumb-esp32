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

class Options {
   public:
    Options();
    ~Options();
    void saveAllOptions();
    void setMaxTime(int maxtime);
    void setCode(String code);
    void setMaxTry(int maxtry);
    void setBrigness(bool on);
    void setFil(int file);

    int getMaxTimeInMin();
    String getCode();
    int getMaxTry();
    int getFil();

   private:
    Preferences *opts;
    int maxTimeInMin = 60;
    String code = "1234567890";
    int maxTry = 3;
    bool brignessOnOff = true;
    int fil = 2;
};

#endif