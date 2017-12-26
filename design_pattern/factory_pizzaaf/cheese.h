#ifndef __cheese_h
#define __cheese_h

#include <string>

class Cheese {
public:
    virtual ~Cheese() {}
    virtual std::string toString() = 0;
};

#endif

