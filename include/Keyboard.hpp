#ifndef _MY_KEYBOARD__
#define _MY_KEYBOARD__

#include <Arduino.h>

#include "interfaces/Peripherique.hpp"

enum KEYBOARD_STATE {IDLE, ENTER_PRESSED, DELETE_PRESSED};
/**
 * Abstract Keyboard
 */
class Keyboard : public Peripherique {
   public:
    KEYBOARD_STATE etat;
    /**
     * lit le contenu tapper au clavier mais reset également.
     */
    String lire();
    String getContent();
    /**
     * reset etat to Idle + clean kbBufferCode
     */
    void fullReset();
    void resetStateOnly();

   protected:
    char matrice[4][4] = {{'1', '2', '3', 'F'},
                          {'4', '5', '6', 'E'},
                          {'7', '8', '9', 'D'},
                          {'A', '0', 'B', 'C'}};
    char rebond;
    String kbBufferCode;
};

#endif