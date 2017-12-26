#ifndef __pizza_store_h
#define __pizza_store_h

#include <string>
#include "pizza.h"

class PizzaStore {
protected: 
    virtual Pizza *createPizza(const std::string &item) = 0;

public:
    Pizza *orderPizza(const std::string &type) {
        Pizza *pizza = createPizza(type);
        std::cout << "--- Making a " << pizza->getName() << " ---\n";
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }
};

#endif
