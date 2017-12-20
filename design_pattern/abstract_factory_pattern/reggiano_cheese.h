#ifndef __reggiano_cheese_h
#define __reggiano_cheese_h

#include <string>
#include "cheese.h"

class ReggianoCheese: public Cheese {
public:
    std::string toString() {
        return "Reggiano Cheese";
    }
};

#endif


