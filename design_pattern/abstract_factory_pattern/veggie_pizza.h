#ifndef __veggie_pizza_h
#define __veggie_pizza_h

#include <iostream>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class VeggiePizza: public Pizza {
private:
    PizzaIngredientFactory *ingredientFactory;

public:
    VeggiePizza(PizzaIngredientFactory *ingredientFactory) {
        this->ingredientFactory = ingredientFactory;
    }

    void prepare() {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        veggies = ingredientFactory->createVeggies();
    }
};

#endif
