#ifndef __ny_style_clam_pizza_h
#define __ny_style_clam_pizza_h

#include "pizza.h"

class NYStyleClamPizza: public Pizza {
public:
    NYStyleClamPizza() {
        name = "NY Style Clam Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";

        toppings.push_back("Grated Reggiano Cheese");
        toppings.push_back("Fresh Clams from Long Island Sound");
    }
};

#endif
