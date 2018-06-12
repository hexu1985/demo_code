#ifndef __world_h
#define __world_h

#include <string>

struct World
{
    World(std::string msg): msg(msg) {}     // added constructor
    World(double a, double b): a(a), b(b) {}    // another constructor
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    double sum_s() { return a + b; }
    std::string msg;
    double a;
    double b;
};

#endif
