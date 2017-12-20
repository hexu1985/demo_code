#ifndef __thick_crust_dough_h
#define __thick_crust_dough_h

#include <string>
#include "dough.h"

class ThickCrustDough: public Dough {
public:
    std::string toString() {
        return "ThickCrust style extra thick crust dough";
    }
};

#endif


