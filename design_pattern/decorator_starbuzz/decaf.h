#ifndef __decaf_h
#define __decaf_h

#include "beverage.h"

class Decaf: public Beverage {
public:
    Decaf(): Beverage("Decaf Coffee") {
    }

    double cost() const override {
        return 1.05;
    }
};

#endif
