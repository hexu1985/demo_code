#ifndef __model_duck_h
#define __model_duck_h

#include <memory>
#include <iostream>
#include "duck.h"
#include "fly_no_way.h"
#include "quack.h"

class ModelDuck: public Duck {
public:
    ModelDuck() {
        flyBehavior = std::make_shared<FlyNoWay>();
        quackBehavior = std::make_shared<Quack>();
    }

    void display() override {
        std::cout << "I'm a model duck\n";
    }
};

#endif
