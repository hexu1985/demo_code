#ifndef __derived_h
#define __derived_h

#include "base.h"

struct Derived : Base {
    std::string getName(); 
};

#endif
