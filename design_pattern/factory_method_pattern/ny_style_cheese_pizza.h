#ifndef __ny_style_cheese_pizza_h
#define __ny_style_cheese_pizza_h

#include "pizza.h"

class NYStyleCheesePizza: public Pizza {
public:
    NYStyleCheesePizza() {
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";

        toppings.push_back("Grated Reggiano Cheese");
    }
};

#endif
