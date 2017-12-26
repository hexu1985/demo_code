#ifndef __ny_style_pepperoni_pizza_h
#define __ny_style_pepperoni_pizza_h

#include "pizza.h"

class NYStylePepperoniPizza: public Pizza {
public:
    NYStylePepperoniPizza() {
        name = "NY Style Pepperoni Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";

        toppings.push_back("Grated Reggiano Cheese");
        toppings.push_back("Sliced Pepperoni");
        toppings.push_back("Garlic");
        toppings.push_back("Onion");
        toppings.push_back("Mushrooms");
        toppings.push_back("Red Pepper");
    }
};

#endif
