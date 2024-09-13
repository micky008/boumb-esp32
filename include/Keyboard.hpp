#ifndef _MY_KEYBOARD__
#define _MY_KEYBOARD__

#include <Arduino.h>
#include "interfaces/Peripherique.hpp"

class  Keyboard : public Peripherique {
public:
    static String kbBufferCode;
    static bool isKbBufferHaveEnterPressed;
    static bool isKbCorrectionPresed;
    static void resetALLKeyboardState();
    static void resetCorrectionKeyboardState();
protected:
    char matrice[4][4] = { {'1', '2', '3', 'F'},
                          {'4', '5', '6', 'E'},
                          {'7', '8', '9', 'D'},
                          {'A', '0', 'B', 'C'} };
    char rebond;
};

#endif