#ifndef __world_h
#define __world_h

#include <string>

struct World
{
    World(std::string msg): msg(msg) {}     // added constructor
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

#endif
