#ifndef _MY_KEYBOARD__
#define _MY_KEYBOARD__

#include <Arduino.h>
#include <PCF8574.h>



class Keyboard {
   public:
    Keyboard(PCF8574 &keyboardI2C);
    static String kbBufferCode;
    static bool isKbBufferHaveEnterPressed;
    static bool isKbCorrectionPresed;
    static void resetALLKeyboardState();
    static void resetCorrectionKeyboardState();
    void lire();

   private:    
    char matrice[4][4] = {{'1', '2', '3', 'F'},
                          {'4', '5', '6', 'E'},
                          {'7', '8', '9', 'D'},
                          {'A', '0', 'B', 'C'}};
    char rebond;
    PCF8574 &keyboardI2C;
};

#endif