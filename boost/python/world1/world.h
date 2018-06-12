#ifndef __world_h
#define __world_h

#include <string>

struct World
{
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

#endif
