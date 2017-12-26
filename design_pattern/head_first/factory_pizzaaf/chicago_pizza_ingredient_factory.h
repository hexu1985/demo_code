#ifndef __chicago_pizza_ingredient_factory_h
#define __chicago_pizza_ingredient_factory_h

#include "pizza_ingredient_factory.h"
#include "thick_crust_dough.h"
#include "plum_tomato_sauce.h"
#include "mozzarella_cheese.h"
#include "black_olives.h"
#include "spinach.h"
#include "eggplant.h"
#include "sliced_pepperoni.h"
#include "frozen_clams.h"

class ChicagoPizzaIngredientFactory: public PizzaIngredientFactory {
public:
    Dough *createDough() {
        return new ThickCrustDough;
    }

    Sauce *createSauce() {
        return new PlumTomatoSauce;
    }

    Cheese *createCheese() {
        return new MozzarellaCheese;
    }

    std::vector<Veggies *> createVeggies() {
        std::vector<Veggies *> veggies = { new BlackOlives, 
                                           new Spinach, 
                                           new Eggplant };
        return veggies;
    }

    Pepperoni *createPepperoni() {
        return new SlicedPepperoni;
    }

    Clams *createClam() {
        return new FrozenClams;
    }
};

#endif
