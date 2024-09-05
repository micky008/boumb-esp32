#include "Options.hpp"

/**
 *     String code = "123456";
    int maxTimeInMin = 60;
    int maxTry = 3;
    bool brignessOnOff = true;
    int fil = 2;
    bool ledOn = true;
 */

Options::Options() {
    initArduino() ;
    address = 0;
    if (!EEPROM.begin(128)){
        Serial2.printf("eeprom feild");
    }
    String res = EEPROM.readString(0);
    if (res == NULL || res.length() == 0) {
        this->saveAllOptions();
        return;
    }
    code = res;
    address += strlen(code.c_str());
    maxTimeInMin = EEPROM.readInt(address);
    address += sizeof(maxTimeInMin);
    maxTry = EEPROM.readInt(address);
    address += sizeof(maxTry);
    brignessOnOff = EEPROM.readBool(address);
    address += sizeof(brignessOnOff);
    fil = EEPROM.readInt(address);
    ledOn = EEPROM.readBool(address);
    Serial.printf("fil=%d\n",fil);
}

void Options::saveAllOptions() {
    address = 0;
    address += EEPROM.writeString(this->address, this->code);
    address += EEPROM.writeInt(address, maxTimeInMin);
    address += EEPROM.writeInt(address, maxTry);
    address += EEPROM.writeBool(address, brignessOnOff);
    address += EEPROM.writeInt(address, fil);
    address += EEPROM.writeBool(address, ledOn);
    EEPROM.commit();
}

void Options::setMaxTime(int maxtime) { maxTimeInMin = maxtime; }
void Options::setCode(String code) { this->code = code; }
void Options::setMaxTry(int maxtry) { this->maxTry = maxtry; }
void Options::setBrigness(bool on) { brignessOnOff = on; }
void Options::setFil(int fil) { this->fil = fil; }
void Options::setLedStatus(bool on) { ledOn = on; }

int Options::getMaxTimeInMin() { return maxTimeInMin; }
String Options::getCode() { return code; }
int Options::getMaxTry() { return maxTry; }
int Options::getFil() { return fil; }
bool Options::getLedStatus() { return ledOn; }
