#include "ny_pizza_store.h"
#include "pizza.h"
#include "ny_style_cheese_pizza.h"
#include "ny_style_pepperoni_pizza.h"
#include "ny_style_clam_pizza.h"
#include "ny_style_veggie_pizza.h"

Pizza *NYPizzaStore::createPizza(const std::string &type) {
    if (type == "cheese") {
        return new NYStyleCheesePizza;
    } else if (type == "veggie") {
        return new NYStyleVeggiePizza;
    } else if (type == "clam") {
        return new NYStyleClamPizza;
    } else if (type == "pepperoni") {
        return new NYStylePepperoniPizza;
    } else
        return NULL;
}
