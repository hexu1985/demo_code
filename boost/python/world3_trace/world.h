#ifndef __world_h
#define __world_h

#include <string>
#include <iostream>

struct World
{
    World(std::string msg): msg(msg) {
        std::cout << "World::World(string msg) called, "
            << "msg = " << msg << ", "
            << "this = " << this << std::endl;
    }     // added constructor

    World(double a, double b): a(a), b(b) {
        std::cout << "World::World(double a, double b) called, "
            << "a = " << a << ", "
            << "b = " << b << ", "
            << "this = " << this << std::endl;
    }    // another constructor

    ~World() {
        std::cout << "World::~World() called, "
            << "this = " << this << std::endl;
    }

    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    double sum_s() { return a + b; }
    std::string msg;
    double a;
    double b;
};

#endif
