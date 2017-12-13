#include <iostream>
#include <memory>
#include "beverage.h"
#include "condiment_decorator.h"
#include "dark_roast.h"
#include "decaf.h"
#include "espresso.h"
#include "house_blend.h"
#include "milk.h"
#include "mocha.h"
#include "soy.h"
#include "whip.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<Beverage> beverage = std::make_shared<Espresso>();
    std::cout << beverage->getDescription() << " $" << beverage->cost() << std::endl;

    std::shared_ptr<Beverage> beverage2 = std::make_shared<DarkRoast>();
    beverage2 = std::make_shared<Mocha>(beverage2);
    beverage2 = std::make_shared<Mocha>(beverage2);
    beverage2 = std::make_shared<Whip>(beverage2);
    std::cout << beverage2->getDescription() << " $" << beverage2->cost() << std::endl;

    std::shared_ptr<Beverage> beverage3 = std::make_shared<HouseBlend>();
    beverage3 = std::make_shared<Soy>(beverage3);
    beverage3 = std::make_shared<Mocha>(beverage3);
    beverage3 = std::make_shared<Whip>(beverage3);
    std::cout << beverage3->getDescription() << " $" << beverage3->cost() << std::endl;

    return 0;
}
