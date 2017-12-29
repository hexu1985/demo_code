#ifndef __rubber_duck_h
#define __rubber_duck_h

#include <memory>
#include <iostream>
#include "duck.h"
#include "fly_no_way.h"
#include "squeak.h"

class RubberDuck: public Duck {
public:
    RubberDuck() {
        flyBehavior = std::make_shared<FlyNoWay>();
        quackBehavior = std::make_shared<Squeak>();
    }

    void display() override {
        std::cout << "I'm a rubber duckie\n";
    }
};

#endif
