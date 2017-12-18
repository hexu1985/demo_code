#ifndef __cheese_pizza_h
#define __cheese_pizza_h

#include "pizza.h"

class CheesePizza: public Pizza {
public:
    CheesePizza() {
        name = "Cheese Pizza";
        dough = "Regular Crust";
        sauce = "Marinara Pizza Sauce";
        toppings.push_back("Fresh Mozzarella");
        toppings.push_back("Parmesan");
    }
};

#endif
