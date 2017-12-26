#ifndef __espresso_h
#define __espresso_h

#include "beverage.h"

class Espresso: public Beverage {
public: 
    Espresso(): Beverage("Espresso")  {
    }

    double cost() const override {
        return 1.99;
    }
};

#endif
