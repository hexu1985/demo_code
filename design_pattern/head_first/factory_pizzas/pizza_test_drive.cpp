#include <memory>
#include <iostream>
#include "simple_pizza_factory.h"
#include "pizza_store.h"

int main(int argc, char *argv[]) {
    SimplePizzaFactory factory;
    PizzaStore store(factory);

    std::unique_ptr<Pizza> pizza; 
    pizza.reset(store.orderPizza("cheese"));
    std::cout << "We ordered a " << pizza->getName() << "\n";

    pizza.reset(store.orderPizza("veggie"));
    std::cout << "We ordered a " << pizza->getName() << "\n";

    std::cout << std::endl;
    return 0;
}

