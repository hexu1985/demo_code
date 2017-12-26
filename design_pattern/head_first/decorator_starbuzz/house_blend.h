#ifndef __house_blend_h
#define __house_blend_h

#include "beverage.h"

class HouseBlend: public Beverage {
public: 
    HouseBlend(): Beverage("House Blend Coffee") {
    }

    double cost() const override {
        return 0.89;
    }
};

#endif
