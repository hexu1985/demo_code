#ifndef __pepperoni_pizza_h
#define __pepperoni_pizza_h

#include "pizza.h"

class PepperoniPizza: public Pizza {
public:
    PepperoniPizza() {
        name = "Pepperoni Pizza";
        dough = "Crust";
        sauce = "Marinara sauce";
        toppings.push_back("Sliced Pepperoni");
        toppings.push_back("Sliced Onion");
        toppings.push_back("Grated parmesan cheese");
    }
};

#endif
