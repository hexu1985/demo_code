#include "simple_pizza_factory.h"
#include "pizza.h"
#include "cheese_pizza.h"
#include "pepperoni_pizza.h"
#include "clam_pizza.h"
#include "veggie_pizza.h"

Pizza *SimplePizzaFactory::createPizza(const std::string &type) {
    Pizza *pizza = NULL;

    if (type == "cheese") {
        pizza = new CheesePizza;
    } else if (type == "pepperoni") {
        pizza = new PepperoniPizza;
    } else if (type == "clam") {
        pizza = new ClamPizza;
    } else if (type == "veggie") {
        pizza = new VeggiePizza;
    }
    return pizza;
}
