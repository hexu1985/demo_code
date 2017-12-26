#ifndef __clam_pizza_h
#define __clam_pizza_h

#include "pizza.h"

class ClamPizza: public Pizza {
public:
    ClamPizza() {
        name = "Clam Pizza";
        dough = "Thin crust";
        sauce = "White garlic sauce";
        toppings.push_back("Clams");
        toppings.push_back("Grated parmesan cheese");
    }
};

#endif
