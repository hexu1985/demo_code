#ifndef __hottub_h
#define __hottub_h

#include <string>
#include <iostream>

class Hottub {
private:
    bool on_ = false;
    int temperature = 0;

public:
    Hottub() {
    }

    void on() {
        on_ = true;
    }

    void off() {
        on_ = false;
    }

    void bubblesOn() {
        if (on_) {
            std::cout << "Hottub is bubbling!" << '\n';
        }
    }

    void bubblesOff() {
        if (on_) {
            std::cout << "Hottub is not bubbling" << '\n';
        }
    }

    void jetsOn() {
        if (on_) {
            std::cout << "Hottub jets are on" << '\n';
        }
    }

    void jetsOff() {
        if (on_) {
            std::cout << "Hottub jets are off" << '\n';
        }
    }

    void setTemperature(int temperature) {
        this->temperature = temperature;
    }

    void heat() {
        temperature = 105;
        std::cout << "Hottub is heating to a steaming 105 degrees" << '\n';
    }

    void cool() {
        temperature = 98;
        std::cout << "Hottub is cooling to 98 degrees" << '\n';
    }
};

#endif
