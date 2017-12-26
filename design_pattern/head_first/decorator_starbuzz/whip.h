#ifndef __whip_h
#define __whip_h

#include <memory>
#include "condiment_decorator.h"

class Whip: public CondimentDecorator {
private:
    std::shared_ptr<Beverage> beverage;

public:
    Whip(std::shared_ptr<Beverage> beverage) {
        this->beverage = beverage;
    }

    std::string getDescription() const override {
        return beverage->getDescription() + ", Whip";
    }

    double cost() const override {
        return 0.10 + beverage->cost();
    }
};

#endif
