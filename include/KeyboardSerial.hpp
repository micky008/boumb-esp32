#ifndef _MY_KEYBOARDSERIAL__
#define _MY_KEYBOARDSERIAL__

#include <Arduino.h>
#include <HardwareSerial.h>
#include "Keyboard.hpp"

#define RXD2 16
#define TXD2 17

class  KeyboardSerial :Keyboard {
public:
    void initKeyboard();
    void lire();
    
};

#endif