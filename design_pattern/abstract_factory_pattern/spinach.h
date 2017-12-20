#ifndef __spinach_h
#define __spinach_h

#include <string>
#include "veggies.h"

class Spinach: public Veggies {
public:
    std::string toString() {
        return "Spinach";
    }
};

#endif


