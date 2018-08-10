#ifndef __theater_lights_h
#define __theater_lights_h

#include <string>

class TheaterLights {
private:
    std::string description;

public:
    TheaterLights(std::string description);

    ~TheaterLights();

    void on();

    void off();

    void dim(int level);

    std::string toString();

    void clear();
};

#endif
