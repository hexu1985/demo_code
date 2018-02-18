#ifndef __light_h
#define __light_h

#include <iostream>
#include <string>

class Light {
private:
    std::string location = "";
    int level = 0;

public:
    Light(std::string location): location(location) {
    }

    void on() {
        level = 100;
        std::cout << location << " light is on\n";
    }

    void off() {
        level = 0;
        std::cout << location << " light is off\n";
    }

    void dim(int level) {
        this->level = level;
        if (level == 0) {
            off();
        } else {
            std::cout << "Light is dimmed to " << level << "%" << '\n';
        }
    }

    int getLevel() {
        return level;
    }
};

#endif
