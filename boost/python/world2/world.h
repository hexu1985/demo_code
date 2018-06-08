#ifndef __word_h
#define __word_h

#include <string>

struct World
{
    World(std::string msg): msg(msg) {}     // added constructor
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

#endif
