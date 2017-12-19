#ifndef __pizza_store_h
#define __pizza_store_h

#include "pizza.h"

class PizzaStore {
public:
    virtual ~PizzaStore() {};

    virtual Pizza *createPizza(const std::string &item) = 0;
 
	Pizza *orderPizza(const std::string &type) {
		Pizza *pizza = createPizza(type);
 
        std::cout << "--- Making a " << pizza->getName() << " ---" << std::endl;
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();

		return pizza;
	}

};

#endif
