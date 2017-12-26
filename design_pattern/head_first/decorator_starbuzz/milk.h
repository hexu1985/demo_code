#ifndef __milk_h
#define __milk_h

#include <memory>
#include "condiment_decorator.h"

class Milk: public CondimentDecorator {
private:
    std::shared_ptr<Beverage> beverage;

public:
    Milk(std::shared_ptr<Beverage> beverage) {
        this->beverage = beverage;
    }

    std::string getDescription() const override {
        return beverage->getDescription() + ", Milk";
    }

    double cost() const override {
        return 0.10 + beverage->cost();
    }
};

#endif
