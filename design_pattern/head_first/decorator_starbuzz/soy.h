#ifndef __soy_h
#define __soy_h

#include <memory>
#include "condiment_decorator.h"

class Soy: public CondimentDecorator {
private:
    std::shared_ptr<Beverage> beverage;

public:
    Soy(std::shared_ptr<Beverage> beverage) {
        this->beverage = beverage;
    }

    std::string getDescription() const override {
        return beverage->getDescription() + ", Soy";
    }

    double cost() const override {
        return 0.15 + beverage->cost();
    }
};

#endif
