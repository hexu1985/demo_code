#ifndef __condiment_decorator_h
#define __condiment_decorator_h

#include <cassert>
#include "beverage.h"

// 佐料装饰者
class CondimentDecorator: public Beverage {
public:
    std::string getDescription() const override
    {
        assert(0 && "need override by derived classes!");
        return Beverage::getDescription();
    }
};

#endif
