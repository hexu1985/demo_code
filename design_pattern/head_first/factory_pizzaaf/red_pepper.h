#ifndef __red_pepper_h
#define __red_pepper_h

#include <string>
#include "veggies.h"

class RedPepper: public Veggies {
public:
    std::string toString() {
        return "Red Pepper";
    }
};

#endif


