#ifndef __fly_rocket_powered_h
#define __fly_rocket_powered_h

#include <iostream>
#include "fly_behavior.h"

class FlyRocketPowered: public FlyBehavior {
public:
    void fly() override {
        std::cout << "I'm flying with a rocket\n";
    }
};

#endif
