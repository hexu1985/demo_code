#ifndef __fly_no_way_h
#define __fly_no_way_h

#include <iostream>
#include "fly_behavior.h"

class FlyNoWay: public FlyBehavior {
public:
    void fly() override {
        std::cout << "I can't fly\n";
    }
};

#endif
