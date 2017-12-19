#ifndef __chicago_style_pepperoni_pizza_h
#define __chicago_style_pepperoni_pizza_h

#include "pizza.h"

class ChicagoStylePepperoniPizza: public Pizza {
public:
    ChicagoStylePepperoniPizza() {
        name = "Chicago Style Pepperoni Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";

        toppings.push_back("Shredded Mozzarella Cheese");
        toppings.push_back("Black Olives");
        toppings.push_back("Spinach");
        toppings.push_back("Eggplant");
        toppings.push_back("Sliced Pepperoni");
    }

    void cut() {
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};

#endif
