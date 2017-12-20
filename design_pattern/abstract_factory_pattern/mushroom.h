#ifndef __mushroom_h
#define __mushroom_h

#include <string>
#include "veggies.h"

class Mushroom: public Veggies {
public:
    std::string toString() {
        return "Mushroom";
    }
};

#endif


