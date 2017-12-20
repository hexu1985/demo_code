#ifndef __chicago_pizza_store_h
#define __chicago_pizza_store_h

#include <string>

class ChicagoPizzaStore: public PizzaStore {
private:
    ChicagoPizzaIngredientFactory ingredientFactory; 

protected: 
    Pizza *createPizza(const std::string &item) {
        Pizza *pizza = 0;

        if (item == "cheese") {

            pizza = new CheesePizza(ingredientFactory);
            pizza->setName("Chicago Style Cheese Pizza");

        } else if (item == "veggie") {

            pizza = new VeggiePizza(ingredientFactory);
            pizza->setName("Chicago Style Veggie Pizza");

        } else if (item == "clam") {

            pizza = new ClamPizza(ingredientFactory);
            pizza->setName("Chicago Style Clam Pizza");

        } else if (item == "pepperoni") {

            pizza = new PepperoniPizza(ingredientFactory);
            pizza->setName("Chicago Style Pepperoni Pizza");

        }

        return pizza;
    }
};

#endif
