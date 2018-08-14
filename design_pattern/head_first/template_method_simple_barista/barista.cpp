#include <iostream>
#include <memory>

#include "tea.h"
#include "coffee.h"

int main(int argc, char *argv[]) {
    auto tea = std::make_shared<Tea>();
    auto coffee = std::make_shared<Coffee>();
    std::cout << "Making tea..." << std::endl;
    tea->prepareRecipe();
    std::cout << "Making coffee..." << std::endl;
    coffee->prepareRecipe();

    return 0;
}
