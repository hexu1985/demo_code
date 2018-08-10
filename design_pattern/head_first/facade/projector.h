#ifndef __projector_h
#define __projector_h

#include <string>
#include <memory>

class DvdPlayer;

class Projector {
private:
    std::string description;
    std::shared_ptr<DvdPlayer> dvdPlayer;

public:
    Projector(std::string description, std::shared_ptr<DvdPlayer> dvdPlayer);

    ~Projector();

    void on();

    void off();

    void wideScreenMode();

    void tvMode();

    std::string toString();

    void clear();
};

#endif
