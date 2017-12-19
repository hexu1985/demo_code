#ifndef __chicago_style_clam_pizza_h
#define __chicago_style_clam_pizza_h

#include "pizza.h"

class ChicagoStyleClamPizza: public Pizza {
public:
    ChicagoStyleClamPizza() {
        name = "Chicago Style Clam Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";

        toppings.push_back("Shredded Mozzarella Cheese");
        toppings.push_back("Frozen Clams from Chesapeake Bay");
    }

    void cut() {
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};

#endif
