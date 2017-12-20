#ifndef __cheese_pizza_h
#define __cheese_pizza_h

#include <iostream>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class CheesePizza: public Pizza {
private:
    PizzaIngredientFactory *ingredientFactory;

public:
    CheesePizza(PizzaIngredientFactory *ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }

    void prepare() {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
    }
};

#endif
