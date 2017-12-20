#ifndef __dough_h
#define __dough_h

#include <string>

class Dough {
public:
    virtual ~Dough() {}
    virtual std::string toString() = 0;
};

#endif

