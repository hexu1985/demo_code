#ifndef __pizza_ingredient_factory_h
#define __pizza_ingredient_factory_h

#include <vector>

class Dough;
class Sauce;
class Cheese;
class Veggies;
class Pepperoni;
class Clams;

class PizzaIngredientFactory {
public:
    virtual ~PizzaIngredientFactory() {}
    virtual Dough *createDough() = 0;
    virtual Sauce *createSauce() = 0;
    virtual Cheese *createCheese() = 0;
    virtual std::vector<Veggies *> createVeggies() = 0;
    virtual Pepperoni *createPepperoni() = 0;
    virtual Clams *createClam() = 0;
};

#endif
