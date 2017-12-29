#ifndef __mute_quack_h
#define __mute_quack_h

#include <iostream>
#include "quack_behavior.h"

class MuteQuack: public QuackBehavior {
public: 
    void quack() override {
        std::cout << "<< Silence >>\n";
    }
};

#endif
