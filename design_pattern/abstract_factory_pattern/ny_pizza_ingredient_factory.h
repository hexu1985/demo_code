#ifndef __ny_pizza_ingredient_factory_h
#define __ny_pizza_ingredient_factory_h

#include "pizza_ingredient_factory.h"
#include "thin_crust_dough.h"
#include "marinara_sauce.h"
#include "reggiano_cheese.h"
#include "garlic.h"
#include "onion.h"
#include "mushroom.h"
#include "sliced_pepperoni.h"
#include "fresh_clams.h"

class NYPizzaIngredientFactory: public PizzaIngredientFactory {
public:
    Dough *createDough() {
        return new ThinCrustDough;
    }

    Sauce *createSauce() {
        return new MarinaraSauce;
    }

    Cheese *createCheese() {
        return new ReggianoCheese;
    }

    std::vector<Veggies *> createVeggies() {
        std::vector<Veggies *> veggies = { new Garlic, new Onion, new Mushroom };
        return veggies;
    }

    Pepperoni *createPepperoni() {
        return new SlicedPepperoni;
    }

    Clams *createClam() {
        return new FreshClams;
    }
};

#endif
