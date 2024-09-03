#ifndef _MY_OPTIONS__
#define _MY_OPTIONS__

#include <Arduino.h>
#include <EEPROM.h>

#define VERSION 2.0

class Options {
   public:
    Options();
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


   private:
    String code = "123456";
    int maxTimeInMin = 60;
    int maxTry = 3;
    bool brignessOnOff = true;
    int fil = 2;
    bool ledOn = true;
    int address = 0;
};

#endif