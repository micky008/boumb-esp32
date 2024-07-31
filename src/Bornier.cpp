#include "Bornier.hpp"

Bornier::Bornier() {
    goodFil = (int)random(1, 5);
    pinMode(25, INPUT_PULLUP);
    pinMode(26, INPUT_PULLUP);
    pinMode(33, INPUT_PULLUP);
    pinMode(32, INPUT_PULLUP);
    pinMode(27, INPUT_PULLDOWN);
    pinMode(14, INPUT_PULLDOWN);
    pinMode(13, INPUT_PULLDOWN);
    pinMode(12, INPUT_PULLDOWN);
}

Bornier::~Bornier() {}

void Bornier::init() {
    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(32, HIGH);
}

bool Bornier::isCut() {
    if (digitalRead(27) == LOW) {
        filCut = 1;
        return true;
    }
    if (digitalRead(26) == LOW) {
        filCut = 2;
        return true;
    }
    if (digitalRead(33) == LOW) {
        filCut = 3;
        return true;
    }
    if (digitalRead(32) == LOW) {
        filCut = 4;
        return true;
    }
    return false;
}

bool Bornier::isGoodFil() { return goodFil == filCut; }