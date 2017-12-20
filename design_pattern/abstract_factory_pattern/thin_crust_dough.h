#ifndef __thin_crust_dough_h
#define __thin_crust_dough_h

#include <string>
#include "dough.h"

class ThinCrustDough: public Dough {
public:
    std::string toString() {
        return "Thin Crust Dough";
    }
};

#endif


