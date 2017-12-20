#ifndef __veggies_h
#define __veggies_h

#include <string>

class Veggies {
public:
    virtual ~Veggies() {}
    virtual std::string toString() = 0;
};

#endif

