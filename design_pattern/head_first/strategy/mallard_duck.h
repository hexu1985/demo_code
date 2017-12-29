#ifndef __mallard_duck_h
#define __mallard_duck_h

#include <memory>
#include <iostream>
#include "duck.h"
#include "fly_with_wings.h"
#include "quack.h"

class MallardDuck: public Duck {
public:
    MallardDuck() {
        quackBehavior = std::make_shared<Quack>();
        flyBehavior = std::make_shared<FlyWithWings>();
    }

    void display() override {
        std::cout << "I'm a real Mallard duck\n";
    }
};

#endif
