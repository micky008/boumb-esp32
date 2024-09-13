#ifndef _MY_KEYBOARDSERIAL__
#define _MY_KEYBOARDSERIAL__

#include <Arduino.h>
#include <HardwareSerial.h>

#include "Keyboard.hpp"

#define RXD2 16
#define TXD2 17

class KeyboardSerial : public Keyboard {
   public:
    void init();
    void scan();
};

#endif