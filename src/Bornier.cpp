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

void Bornier::setFil(int fil) {
    if (fil == -1) {
        goodFil = (int)random(1, 5);
    }
    else {
        goodFil = fil;
    }
}

int Bornier::getFil() {
    return goodFil;
}

bool Bornier::isCut() {
    if (filCut > -1) {
        return true;
    }
    if (digitalRead(27) == LOW) {
        filCut = 1;
        return true;
    }
    if (digitalRead(14) == LOW) {
        filCut = 2;
        return true;
    }
    if (digitalRead(12) == LOW) {
        filCut = 3;
        return true;
    }
    if (digitalRead(13) == LOW) {
        filCut = 4;
        return true;
    }
    return false;
}

bool Bornier::isGoodFil() { return goodFil == filCut; }