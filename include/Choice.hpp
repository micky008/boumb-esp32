#ifndef _MY_CHOICE__
#define _MY_CHOICE__

#include <Arduino.h>

#include "Keyboard.hpp"
#include "LCD.hpp"

class Choice {
   public:
    Choice(MyLCD& lcd);
    String theChoice(String lineUp, String lineDown);

   private:
    MyLCD& lcd;
};

#endif
