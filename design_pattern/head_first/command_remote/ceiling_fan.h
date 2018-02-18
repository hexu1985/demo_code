#ifndef __ceiling_fan_h
#define __ceiling_fan_h

#include <string>
#include <iostream>

class CeilingFan {
private:
    std::string location = "";
    int level = 0;

public:
    static const int HIGH = 2;
    static const int MEDIUM = 1;
    static const int LOW = 0;
 
    CeilingFan(const std::string &location): location(location) {
    }
  
    void high() {
        // turns the ceiling fan on to high
        level = HIGH;
        std::cout << location << " ceiling fan is on high" << '\n';
    } 

    void medium() {
        // turns the ceiling fan on to medium
        level = MEDIUM;
        std::cout << location << " ceiling fan is on medium" << '\n';
    }

    void low() {
        // turns the ceiling fan on to low
        level = LOW;
        std::cout << location << " ceiling fan is on low" << '\n';
    }
 
    void off() {
        // turns the ceiling fan off
        level = 0;
        std::cout << location << " ceiling fan is off" << '\n';
    }
 
    int getSpeed() {
        return level;
    }
};

#endif
