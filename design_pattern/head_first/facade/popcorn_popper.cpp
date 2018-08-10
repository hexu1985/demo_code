#include <iostream>
#include "popcorn_popper.h"

PopcornPopper::PopcornPopper(std::string description) {
    std::cout << "create PopcornPopper: " << description << std::endl;
    this->description = description;
}

PopcornPopper::~PopcornPopper() {
    std::cout << "destroy PopcornPopper: " << description << std::endl;
}

void PopcornPopper::on() {
    std::cout << description << " on" << std::endl;
}

void PopcornPopper::off() {
    std::cout << description << " off" << std::endl;
}

void PopcornPopper::pop() {
    std::cout << description << " popping popcorn!" << std::endl;
}

std::string PopcornPopper::toString() {
    return description;
}

void PopcornPopper::clear() {
}
