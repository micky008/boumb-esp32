#include "Bornier.hpp"

Bornier::Bornier() {
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(27, INPUT_PULLDOWN);
    pinMode(14, INPUT_PULLDOWN);
    pinMode(13, INPUT_PULLDOWN);
    pinMode(12, INPUT_PULLDOWN);
}
void Bornier::init() {
    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(32, HIGH);
}

void Bornier::applyOption(OptionBornier& oBornier) {
    int filTmp = static_cast<int>(oBornier.getFil());
    if (filTmp == -1) {
        goodFil = (int)random(1, 5);
    } else {
        goodFil = filTmp;
    }
}

void Bornier::lire() {
    if (filCut > -1) {
        return;
    }
    if (digitalRead(27) == LOW) {
        filCut = 1;
    }
    if (digitalRead(14) == LOW) {
        filCut = 2;
    }
    if (digitalRead(12) == LOW) {
        filCut = 3;
    }
    if (digitalRead(13) == LOW) {
        filCut = 4;
    }
}

BORNIER_ETAT Bornier::getEtat() {
    if (filCut == -1) {
        return BORNIER_ETAT::ALL_FILS_OK;
    }
    if (goodFil == filCut) {
        return BORNIER_ETAT::GOOD_FIL;
    }
    return BORNIER_ETAT::WRONG_FIL;
}