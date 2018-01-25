#ifndef __garage_door_h
#define __garage_door_h

#include <iostream>

class GarageDoor {
public:
    GarageDoor() {}

    void up() {
        std::cout << "Garage Door is Open\n";
    }

    void down() {
        std::cout << "Garage Door is Closed\n";
    }

    void stop() {
        std::cout << "Garage Door is Stopped\n";
    }

    void lightOn() {
        std::cout << "Garage light is on\n";
    }

    void lightOff() {
        std::cout << "Garage light is off\n";
    }
};

#endif
