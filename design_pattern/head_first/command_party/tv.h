#ifndef __tv_h
#define __tv_h

#include <string>
#include <iostream>

class TV {
private:
    std::string location;
    int channel;

public:
    TV(const std::string &location): location(location) {
    }

    void on() {
        std::cout << location << " TV is on" << '\n';
    }

    void off() {
        std::cout << location << " TV is off" << '\n';
    }

    void setInputChannel() {
        channel = 3;
        std::cout << location << " TV channel is set for DVD" << '\n';
    }
};

#endif
