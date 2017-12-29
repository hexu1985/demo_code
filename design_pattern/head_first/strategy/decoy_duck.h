#ifndef __decoy_duck_h
#define __decoy_duck_h

#include <memory>
#include <iostream>
#include "duck.h"
#include "fly_no_way.h"
#include "mute_quack.h"

class DecoyDuck: public Duck {
public:
    DecoyDuck() {
        setFlyBehavior(std::make_shared<FlyNoWay>());
        setQuackBehavior(std::make_shared<MuteQuack>());
    }

    void display() override {
        std::cout << "I'm a duck Decoy\n";
    }
};

#endif
