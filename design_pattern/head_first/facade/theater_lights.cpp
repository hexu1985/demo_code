#include <iostream>
#include "theater_lights.h"

TheaterLights::TheaterLights(std::string description) {
    std::cout << "create TheaterLights: " << description << std::endl;
    this->description = description;
}

TheaterLights::~TheaterLights() {
    std::cout << "destroy TheaterLights: " << description << std::endl;
}

void TheaterLights::on() {
    std::cout << description << " on" << std::endl;
}

void TheaterLights::off() {
    std::cout << description << " off" << std::endl;
}

void TheaterLights::dim(int level) {
    std::cout << description << " dimming to " << level  << "%" << std::endl;
}

std::string TheaterLights::toString() {
    return description;
}

void TheaterLights::clear() {
}
