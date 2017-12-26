#ifndef __pepperoni_h
#define __pepperoni_h

#include <string>

class Pepperoni {
public:
    virtual ~Pepperoni() {}
    virtual std::string toString() = 0;
};

#endif

