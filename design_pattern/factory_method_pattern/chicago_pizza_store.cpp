#include "chicago_pizza_store.h"
#include "pizza.h"
#include "chicago_style_cheese_pizza.h"
#include "chicago_style_pepperoni_pizza.h"
#include "chicago_style_clam_pizza.h"
#include "chicago_style_veggie_pizza.h"

Pizza *ChicagoPizzaStore::createPizza(const std::string &type) {
    if (type == "cheese") {
        return new ChicagoStyleCheesePizza;
    } else if (type == "veggie") {
        return new ChicagoStyleVeggiePizza;
    } else if (type == "clam") {
        return new ChicagoStyleClamPizza;
    } else if (type == "pepperoni") {
        return new ChicagoStylePepperoniPizza;
    } else
        return NULL;
}
