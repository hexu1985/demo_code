#ifndef __chicago_pizza_store_h
#define __chicago_pizza_store_h

#include "pizza.h"
#include "pizza_store.h"

class ChicagoPizzaStore: public PizzaStore {
public:
    Pizza *createPizza(const std::string &type);
};

#endif
