#ifndef __clams_h
#define __clams_h

#include <string>

class Clams {
public:
    virtual ~Clams() {}
    virtual std::string toString() = 0;
};

#endif

