#ifndef __simple_pizza_factory_h
#define __simple_pizza_factory_h

#include "pizza.h"

class SimplePizzaFactory {
public:
    Pizza *createPizza(const std::string &type);
};

#endif
