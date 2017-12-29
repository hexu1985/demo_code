#ifndef __fake_quack_h
#define __fake_quack_h

#include <iostream>
#include "quack_behavior.h"

class FakeQuack: public QuackBehavior {
public: 
    void quack() override {
        std::cout << "Qwak\n";
    }
};

#endif
