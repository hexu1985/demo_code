#ifndef __stereo_h
#define __stereo_h

#include <string>
#include <iostream>

class Stereo {
private:
    std::string location;

public:
    Stereo(const std::string &location): location(location) {
    }

    void on() {
        std::cout << location <<  " stereo is on" << '\n';
    }

    void off() {
        std::cout << location <<  " stereo is off" << '\n';
    }

    void setCD() {
        std::cout << location <<  " stereo is set for CD input" << '\n';
    }

    void setDVD() {
        std::cout << location <<  " stereo is set for DVD input" << '\n';
    }

    void setRadio() {
        std::cout << location <<  " stereo is set for Radio" << '\n';
    }

    void setVolume(int volume) {
        // code to set the volume
        // valid range: 1-11 (after all 11 is better than 10, right?)
        std::cout << location <<  " Stereo volume set to " << '\n';
    }
};

#endif
