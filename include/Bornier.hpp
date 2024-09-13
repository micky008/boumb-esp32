#ifndef _MY_BORNIER__
#define _MY_BORNIER__

#include <Arduino.h>

#include "interfaces/Peripherique.hpp"
#include "interfaces/options/OBornier.hpp"

enum BORNIER_ETAT { ALL_FILS_OK, WRONG_FIL, GOOD_FIL };

class Bornier : Peripherique {
   public:
    Bornier();
    void init();
    void applyOption(OptionBornier& obornier);
    void lire();
    BORNIER_ETAT getEtat();

   private:
    int goodFil;
    int filCut = -1;
};

#endif