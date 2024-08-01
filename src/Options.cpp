#include "Options.hpp"

Options::Options() {
    opts = new Preferences();
    opts->begin("myPrefs", false);
    if (opts->isKey(OPT_BRIGNESS) == false) {
        opts->putLong(OPT_MAX_TIME, maxTimeInMin);
        opts->putString(OPT_CODE, code);
        opts->putInt(OPT_MAX_TRY, maxTry);
        opts->putInt(OPT_FIL_BORNIER, fil);
        opts->putBool(OPT_BRIGNESS, brignessOnOff);
    } else {
        maxTimeInMin = opts->getLong(OPT_MAX_TIME);
        code = opts->getString(OPT_CODE);
        maxTry = opts->getInt(OPT_MAX_TRY);
        fil = opts->getInt(OPT_FIL_BORNIER);
        brignessOnOff = opts->getBool(OPT_BRIGNESS);
    }
}

void Options::saveAllOptions() {
    opts->putLong(OPT_MAX_TIME, maxTimeInMin);
    opts->putString(OPT_CODE, code);
    opts->putInt(OPT_MAX_TRY, maxTry);
    opts->putInt(OPT_FIL_BORNIER, fil);
    opts->putBool(OPT_BRIGNESS, brignessOnOff);
}

void Options::setMaxTime(int maxtime) { maxTimeInMin = maxtime; }
void Options::setCode(String code) { this->code = code; }
void Options::setMaxTry(int maxtry) { this->maxTry = maxtry; }
void Options::setBrigness(bool on) { brignessOnOff = on; }
void Options::setFil(int fil) { this->fil = fil; }

Options::~Options() { delete opts; }
int Options::getMaxTimeInMin() { return maxTimeInMin; }
String Options::getCode() { return code; }
int Options::getMaxTry() { return maxTry; }
int Options::getFil() { return fil; }