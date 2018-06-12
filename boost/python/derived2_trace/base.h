#ifndef __base_h
#define __base_h

#include <string>

struct Base {
    Base();
    virtual ~Base();
    virtual std::string getName();

    std::string str;
};

#endif
