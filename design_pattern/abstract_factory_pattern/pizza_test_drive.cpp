#include <memory>
#include <iostream>
#include "chicago_pizza_store.h"
#include "ny_pizza_store.h"
#include "pizza_store.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<PizzaStore> nyStore(new NYPizzaStore);
    std::unique_ptr<PizzaStore> chicagoStore(new ChicagoPizzaStore);

    std::unique_ptr<Pizza> pizza;
    pizza.reset(nyStore->orderPizza("cheese"));
    std::cout << "Ethan ordered a " << pizza->toString() << "\n\n";

    pizza.reset(chicagoStore->orderPizza("cheese"));
    std::cout << "Joel ordered a " << pizza->toString() << "\n\n";

    pizza.reset(nyStore->orderPizza("clam"));
    std::cout << "Ethan ordered a " << pizza->toString() << "\n\n";

    pizza.reset(chicagoStore->orderPizza("clam"));
    std::cout << "Joel ordered a " << pizza->toString() << "\n\n";

    pizza.reset(nyStore->orderPizza("pepperoni"));
    std::cout << "Ethan ordered a " << pizza->toString() << "\n\n";

    pizza.reset(chicagoStore->orderPizza("pepperoni"));
    std::cout << "Joel ordered a " << pizza->toString() << "\n\n";

    pizza.reset(nyStore->orderPizza("veggie"));
    std::cout << "Ethan ordered a " << pizza->toString() << "\n\n";

    pizza.reset(chicagoStore->orderPizza("veggie"));
    std::cout << "Joel ordered a " << pizza->toString() << "\n\n";

    return 0;
}

