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

    void circulate() {
        if (on_) {
            std::cout << "Hottub is bubbling!" << '\n';
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
        if (temperature > this->temperature) {
            std::cout << "Hottub is heating to a steaming " << temperature << " degrees" << '\n';
        } else {
            std::cout << "Hottub is cooling to " << temperature << " degrees" << '\n';
        }
        this->temperature = temperature;
    }
};

#endif
