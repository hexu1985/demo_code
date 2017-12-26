#ifndef __ny_pizza_store_h
#define __ny_pizza_store_h

#include "pizza.h"
#include "pizza_store.h"

class NYPizzaStore: public PizzaStore {
public:
    Pizza *createPizza(const std::string &type);
};

#endif
