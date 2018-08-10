#include <iostream>
#include "tuner.h"

Tuner::Tuner(std::string description, std::shared_ptr<Amplifier> amplifier) {
    std::cout << "create Tuner: " << description << std::endl;
    this->description = description;
}

Tuner::~Tuner() {
    std::cout << "destroy Tuner: " << description << std::endl;
    this->description = description;
}

void Tuner::on() {
    std::cout << description << " on" << std::endl;
}

void Tuner::off() {
    std::cout << description << " off" << std::endl;
}

void Tuner::setFrequency(double frequency) {
    std::cout << description << " setting frequency to " << frequency << std::endl;
    this->frequency = frequency;
}

void Tuner::setAm() {
    std::cout << description << " setting AM mode" << std::endl;
}

void Tuner::setFm() {
    std::cout << description << " setting FM mode" << std::endl;
}

std::string Tuner::toString() {
    return description;
}

void Tuner::clear() {
    amplifier = nullptr;
}
