#ifndef _MY_KEYBOARD__
#define _MY_KEYBOARD__

#include <Arduino.h>

class Keyboard {
   public:
    static String kbBufferCode;
    static bool isKbBufferHaveEnterPressed;
    static bool isKbCorrectionPresed;
    static void resetKeyboardState();
};

#endif