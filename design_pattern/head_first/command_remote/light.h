#ifndef __light_h
#define __light_h

#include <iostream>
#include <string>

class Light {
private:
    std::string location = "";

public:
    Light(std::string location): location(location) {
    }

    void on() {
        std::cout << location << " light is on\n";
    }

    void off() {
        std::cout << location << " light is off\n";
    }
};

#endif
