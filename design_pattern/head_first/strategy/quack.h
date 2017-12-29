#ifndef __quack_h
#define __quack_h

#include <iostream>
#include "quack_behavior.h"

class Quack: public QuackBehavior {
public: 
    void quack() override {
        std::cout << "Quack\n";
    }
};

#endif
