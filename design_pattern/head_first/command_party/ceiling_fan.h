#ifndef __ceiling_fan_h
#define __ceiling_fan_h

#include <string>
#include <iostream>

class CeilingFan {
private:
    std::string location = "";
    int speed = 0;

public:
    static const int HIGH = 3;
    static const int MEDIUM = 2;
    static const int LOW = 1;
    static const int OFF = 0;
 
    CeilingFan(const std::string &location): location(location) {
    }
  
    void high() {
        // turns the ceiling fan on to high
        speed = HIGH;
        std::cout << location << " ceiling fan is on high" << '\n';
    } 

    void medium() {
        // turns the ceiling fan on to medium
        speed = MEDIUM;
        std::cout << location << " ceiling fan is on medium" << '\n';
    }

    void low() {
        // turns the ceiling fan on to low
        speed = LOW;
        std::cout << location << " ceiling fan is on low" << '\n';
    }
 
    void off() {
        // turns the ceiling fan off
        speed = OFF;
        std::cout << location << " ceiling fan is off" << '\n';
    }
 
    int getSpeed() {
        return speed;
    }
};

#endif
