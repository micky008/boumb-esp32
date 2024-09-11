#ifndef _MY_BORNIER__
#define _MY_BORNIER__

#include <Arduino.h>
#include "interfaces/Peripherique.hpp"

class Bornier :Peripherique {
public:
    Bornier();
    void init();
    bool isCut();
    bool isGoodFil();
    void setFil(int fil);
    int getFil();
    void lire();
private:
    int goodFil;
    int filCut = -1;
};


#endif