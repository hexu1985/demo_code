#ifndef __red_head_duck_h
#define __red_head_duck_h

#include <memory>
#include <iostream>
#include "duck.h"
#include "fly_with_wings.h"
#include "quack.h"

class RedHeadDuck: public Duck {
public:
    ModelDuck() {
        flyBehavior = std::make_shared<FlyWithWings>();
        quackBehavior = std::make_shared<Quack>();
    }

    void display() override {
        std::cout << "I'm a real Red Headed duck\n";
    }
};

#endif
