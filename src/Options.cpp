#include "Options.hpp"


Options::Options() {
    
    

}
void Options::initOptions() {
    opts = new Preferences();
    opts->begin("myPrefs", false);
    if (opts->isKey(OPT_BRIGNESS) == false) {
        this->saveAllOptions();
    }
    else {
        maxTimeInMin = opts->getLong(OPT_MAX_TIME);
        code = opts->getString(OPT_CODE);
        maxTry = opts->getInt(OPT_MAX_TRY);
        fil = opts->getInt(OPT_FIL_BORNIER);
        brignessOnOff = opts->getBool(OPT_BRIGNESS);
        ledOn = opts->getBool(OPT_LED_ON_OFF);
    }
}

Options::~Options() { delete opts; }

void Options::saveAllOptions() {
    opts->putLong(OPT_MAX_TIME, maxTimeInMin);
    opts->putString(OPT_CODE, code);
    opts->putInt(OPT_MAX_TRY, maxTry);
    opts->putInt(OPT_FIL_BORNIER, fil);
    opts->putBool(OPT_BRIGNESS, brignessOnOff);
    opts->putBool(OPT_LED_ON_OFF, ledOn);
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
bool Options::getBrigntnessStatus() { return brignessOnOff; }

