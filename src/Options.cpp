#include "Options.hpp"

void Options::init() {
    opts = new Preferences();
    opts->begin("myPrefs", false);
    if (opts->isKey(OPT_BRIGNESS) == false) {
        this->saveAllOptions();
    } else {
        maxTimeInMin = opts->getLong(OPT_MAX_TIME);
        code = opts->getString(OPT_CODE);
        maxTry = opts->getInt(OPT_MAX_TRY);
        fil = opts->getInt(OPT_FIL_BORNIER);
        brignessOnOff = opts->getBool(OPT_BRIGNESS);
        ledOn = opts->getBool(OPT_LED_ON_OFF);
    }
}
void Options::saveAllOptions() {
    opts->putLong(OPT_MAX_TIME, maxTimeInMin);
    opts->putString(OPT_CODE, code);
    opts->putInt(OPT_MAX_TRY, maxTry);
    opts->putInt(OPT_FIL_BORNIER, fil);
    opts->putBool(OPT_BRIGNESS, brignessOnOff);
    opts->putBool(OPT_LED_ON_OFF, ledOn);
}

void Options::setMaxTimeInMin(uint16_t maxtime) { maxTimeInMin = maxtime; }
void Options::setCode(String code) { this->code = code; }
void Options::setMaxTry(uint8_t maxtry) { this->maxTry = maxtry; }
void Options::setBrignessOn(bool on) { brignessOnOff = on; }
void Options::setFil(FIL_BORNIER fil) { this->fil = static_cast<int>(fil); }
void Options::setLedOn(bool on) { ledOn = on; }

uint16_t Options::getMaxTimeInMin() { return maxTimeInMin; }
String Options::getCode() { return code; }
uint8_t Options::getMaxTry() { return maxTry; }
FIL_BORNIER Options::getFil() { return FIL_BORNIER(fil); }
bool Options::isLEDOn() { return ledOn; }
bool Options::getBrigtnessOn() { return brignessOnOff; }

int Options::getInitialTime() {
    return maxTimeInMin * 60000;
}  // trick only for LED
