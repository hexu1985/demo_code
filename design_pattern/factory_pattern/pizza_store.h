#ifndef __pizza_store_h
#define __pizza_store_h

#include "simple_pizza_factory.h"

class PizzaStore {
private:
	SimplePizzaFactory factory;
 
public:
	PizzaStore(const SimplePizzaFactory &factory) { 
		this->factory = factory;
	}
 
	Pizza *orderPizza(const std::string &type) {
		Pizza *pizza;
 
		pizza = factory.createPizza(type);
 
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();

		return pizza;
	}

};

#endif
