#ifndef __frozen_clams_h
#define __frozen_clams_h

#include <string>
#include "clams.h"

class FrozenClams: public Clams {
public:
    std::string toString() {
        return "Frozen Clams from Chesapeake Bay";
    }
};

#endif


