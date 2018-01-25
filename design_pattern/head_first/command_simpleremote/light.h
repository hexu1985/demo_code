#ifndef __light_h
#define __light_h

#include <iostream>

class Light {
public:
    Light() {
    }

    void on() {
        std::cout << "Light is on\n";
    }

    void off() {
        std::cout << "Light is off\n";
    }
};

#endif
