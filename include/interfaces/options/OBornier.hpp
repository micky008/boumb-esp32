#ifndef __OPTIONBORNIER_H__
#define __OPTIONBORNIER_H__

enum FIL_BORNIER {
    FIL_RANDOM = -1,
    FIL_1 = 1,
    FIL_2 = 2,
    FIL_3 = 3,
    FIL_4 = 4
};

class OptionBornier {
   public:
    virtual FIL_BORNIER getFil() = 0;
    virtual void setFil(FIL_BORNIER fil) = 0;
};

#endif