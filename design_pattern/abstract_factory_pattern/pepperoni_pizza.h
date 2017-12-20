#ifndef __pepperoni_pizza_h
#define __pepperoni_pizza_h

#include <iostream>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class PepperoniPizza: public Pizza {
private:
    PizzaIngredientFactory *ingredientFactory;

public:
    PepperoniPizza(PizzaIngredientFactory *ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }

    void prepare() {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        veggies = ingredientFactory->createVeggies();
        pepperoni = ingredientFactory->createPepperoni();
    }
};

#endif
