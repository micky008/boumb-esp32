#ifndef _MY_KEYBOARDWIRE__
#define _MY_KEYBOARDWIRE__

#include <Arduino.h>
#include "Keyboard.hpp"
#include <Wire.h>
#include <math.h>

#define MODULE_ADDRESS 0x20
#define DEBOUNCE 500

#define toBit(number) (1UL << (number))

/**
 * C'est comme KeyboardLibPCF8574 mais sans la lib
 * c'est une utilisation RAW de l'i2c
 */
class  KeyboardWire : public Keyboard {
public:
  void init();
  void lire();
private:
  bool digitalRead(int pin);
//247 ligne 1
//251 ligne 4
//253 ligne 7
//254 ligne A
  byte row[4] = { 247,251,253,254 }; // a convertir en binaire (0bxxxxxxx)pour mieux comprendre.
  int oldx = -1;
  long lastDebonce;
};

#endif