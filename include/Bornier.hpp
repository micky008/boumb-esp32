#ifndef _MY_BORNIER__
#define _MY_BORNIER__

#include <Arduino.h>

class Bornier {
    public:
    Bornier();
    ~Bornier();
        void init();
        bool isCut();
        bool isGoodFil();
    private:
        int goodFil;
        int filCut = -1;
};


#endif