#ifndef __var_h
#define __var_h

#include <string>

struct Var
{
    Var(std::string name) : name(name), value() {}
    std::string const name;
    float value;
};

#endif
