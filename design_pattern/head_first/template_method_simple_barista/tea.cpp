#include <iostream>
#include "tea.h" 

void Tea::prepareRecipe() {
    boilWater();
    steepTeaBag();
    pourInCup();
    addLemon();
}

void Tea::boilWater() {
    std::cout << "Boiling water" << std::endl;
}

void Tea::steepTeaBag() {
    std::cout << "Steeping the tea" << std::endl;
}

void Tea::addLemon() {
    std::cout << "Adding Lemon" << std::endl;
}

void Tea::pourInCup() {
    std::cout << "Pouring into cup" << std::endl;
}

