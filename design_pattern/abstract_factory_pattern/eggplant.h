#ifndef __eggplant_h
#define __eggplant_h

#include <string>
#include "veggies.h"

class Eggplant: public Veggies {
public:
    std::string toString() {
        return "Eggplant";
    }
};

#endif


