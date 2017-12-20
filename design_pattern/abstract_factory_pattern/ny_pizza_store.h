#ifndef __ny_pizza_store_h
#define __ny_pizza_store_h

#include <string>
#include "pizza.h"
#include "pizza_store.h"
#include "cheese_pizza.h"
#include "veggie_pizza.h"
#include "clam_pizza.h"
#include "pepperoni_pizza.h"
#include "ny_pizza_ingredient_factory.h"

class NYPizzaStore: public PizzaStore {
private:
    NYPizzaIngredientFactory ingredientFactory; 

protected: 
    Pizza *createPizza(const std::string &item) {
        Pizza *pizza = 0;

        if (item == "cheese") {

            pizza = new CheesePizza(&ingredientFactory);
            pizza->setName("New York Style Cheese Pizza");

        } else if (item == "veggie") {

            pizza = new VeggiePizza(&ingredientFactory);
            pizza->setName("New York Style Veggie Pizza");

        } else if (item == "clam") {

            pizza = new ClamPizza(&ingredientFactory);
            pizza->setName("New York Style Clam Pizza");

        } else if (item == "pepperoni") {

            pizza = new PepperoniPizza(&ingredientFactory);
            pizza->setName("New York Style Pepperoni Pizza");

        }

        return pizza;
    }
};

#endif
