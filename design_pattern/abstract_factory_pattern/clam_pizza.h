#ifndef __clam_pizza_h
#define __clam_pizza_h

#include <iostream>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class ClamPizza: public Pizza {
private:
    PizzaIngredientFactory *ingredientFactory;

public: 
    ClamPizza(PizzaIngredientFactory *ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }

    void prepare() {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        clam = ingredientFactory->createClam();
    }
};

#endif
