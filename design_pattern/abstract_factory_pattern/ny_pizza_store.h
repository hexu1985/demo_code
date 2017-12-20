#ifndef __chicago_pizza_store_h
#define __chicago_pizza_store_h

#include <string>

class ChicagoPizzaStore: public PizzaStore {
private:
    NYPizzaIngredientFactory ingredientFactory; 

protected: 
    Pizza *createPizza(const std::string &item) {
        Pizza *pizza = 0;

        if (item == "cheese") {

            pizza = new CheesePizza(ingredientFactory);
            pizza->setName("New York Style Cheese Pizza");

        } else if (item == "veggie") {

            pizza = new VeggiePizza(ingredientFactory);
            pizza->setName("New York Style Veggie Pizza");

        } else if (item == "clam") {

            pizza = new ClamPizza(ingredientFactory);
            pizza->setName("New York Style Clam Pizza");

        } else if (item == "pepperoni") {

            pizza = new PepperoniPizza(ingredientFactory);
            pizza->setName("New York Style Pepperoni Pizza");

        }

        return pizza;
    }
};

#endif
