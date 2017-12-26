#ifndef __sauce_h
#define __sauce_h

#include <string>

class Sauce {
public:
    virtual ~Sauce() {}
    virtual std::string toString() = 0;
};

#endif

