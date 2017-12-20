#ifndef __sliced_pepperoni_h
#define __sliced_pepperoni_h

#include <string>
#include "pepperoni.h"

class SlicedPepperoni: public Pepperoni {
public:
    std::string toString() {
        return "Sliced Pepperoni";
    }
};

#endif


