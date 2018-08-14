#include <iostream>
#include "coffee.h"

void Coffee::prepareRecipe() {
    boilWater();
    brewCoffeeGrinds();
    pourInCup();
    addSugarAndMilk();
}

void Coffee::boilWater() {
    std::cout << "Boiling water" << std::endl;
}

void Coffee::brewCoffeeGrinds() {
    std::cout << "Dripping Coffee through filter" << std::endl;
}

void Coffee::pourInCup() {
    std::cout << "Pouring into cup" << std::endl;
}

void Coffee::addSugarAndMilk() {
    std::cout << "Adding Sugar and Milk" << std::endl;
}
