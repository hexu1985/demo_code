#ifndef __fly_with_wings_h
#define __fly_with_wings_h

#include <iostream>
#include "fly_behavior.h"

class FlyWithWings: public FlyBehavior {
public:
    void fly() override {
        std::cout << "I'm flying!!\n";
    }
};

#endif
