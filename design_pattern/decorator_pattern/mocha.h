#ifndef __mocha_h
#define __mocha_h

#include <memory>
#include "condiment_decorator.h"

class Mocha: public CondimentDecorator {
private:
    std::shared_ptr<Beverage> beverage;

public:
    Mocha(std::shared_ptr<Beverage> beverage) {
        this->beverage = beverage;
    }

    std::string getDescription() const override {
        return beverage->getDescription() + ", Mocha";
    }

    double cost() const override {
        return 0.20 + beverage->cost();
    }
};

#endif
