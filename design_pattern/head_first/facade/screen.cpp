#include "screen.h"
#include <iostream>

Screen::Screen(std::string description) {
    std::cout << "create Screen: " << description << std::endl;
    this->description = description;
}

Screen::~Screen() {
    std::cout << "destroy Screen: " << description << std::endl;
}

void Screen::up() {
    std::cout << description << " going up" << std::endl;
}

void Screen::down() {
    std::cout << description << " going down" << std::endl;
}

std::string Screen::toString() {
    return description;
}

void Screen::clear() {
}
