#ifndef __dark_roast_h
#define __dark_roast_h

#include "beverage.h"

class DarkRoast: public Beverage {
public:
    DarkRoast(): Beverage("Dark Roast Coffee") {
    }

    double cost() const override {
        return 0.99;
    }
};

#endif
