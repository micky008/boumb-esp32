#ifndef _MY_KEYBOARDWIRE__
#define _MY_KEYBOARDWIRE__

#include <Arduino.h>
#include "Keyboard.hpp"
#include <Wire.h>
#include <math.h>

#define MODULE_ADDRESS 0x20

#define toBit(number) (1UL << (number))


class  KeyboardWire : Keyboard {
public:
  void initKeyboard();
  void lire();
private:
  bool digitalRead(int pin);
//247 ligne 1
//251 ligne 4
//253 ligne 7
//254 ligne A
  byte row[4] = { 247,251,253,254 };
};

#endif