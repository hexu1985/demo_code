#ifndef __derived_h
#define __derived_h

#include "base.h"

struct Derived : Base {
    Derived();
    ~Derived() override;
    std::string getName() override; 
};

#endif
