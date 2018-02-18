#ifndef __garage_door_h
#define __garage_door_h

#include <iostream>

class GarageDoor {
private:
    std::string location;

public:
    GarageDoor(const std::string &location): location(location) {}

    void up() {
        std::cout << location << " garage Door is Up" << '\n';
    }

    void down() {
        std::cout << location << " garage Door is Down" << '\n';
    }

    void stop() {
        std::cout << location << " garage Door is Stopped" << '\n';
    }

    void lightOn() {
        std::cout << location << " garage light is on" << '\n';
    }

    void lightOff() {
        std::cout << location << " garage light is off" << '\n';
    }
};

#endif
