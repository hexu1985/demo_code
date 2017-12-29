#ifndef __squeak_h
#define __squeak_h

#include <iostream>
#include "quack_behavior.h"

class Squeak: public QuackBehavior {
public: 
    void quack() override {
        std::cout << "Squeak\n";
    }
};

#endif
