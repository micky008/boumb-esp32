#ifndef _MY_KEYBOARDLIBPCF8574__
#define _MY_KEYBOARDLIBPCF8574__

#include <Arduino.h>
#include <PCF8574.h>
#include "Keyboard.hpp"

class  KeyboardLibPCF8574 : Keyboard {
public:
  KeyboardLibPCF8574();
  ~KeyboardLibPCF8574();
  void initKeyboard();
  void lire();
private:
  PCF8574* keyboardI2C;
};

#endif