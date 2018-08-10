#include "projector.h"
#include <iostream>

Projector::Projector(std::string description, std::shared_ptr<DvdPlayer> dvdPlayer) {
    std::cout << "create Projector: " << description << std::endl;
    this->description = description;
    this->dvdPlayer = dvdPlayer;
}

Projector::~Projector() {
    std::cout << "destroy Projector: " << description << std::endl;
}

void Projector::on() {
    std::cout << description << " on" << std::endl;
}

void Projector::off() {
    std::cout << description << " off" << std::endl;
}

void Projector::wideScreenMode() {
    std::cout << description << " in widescreen mode (16x9 aspect ratio)" << std::endl;
}

void Projector::tvMode() {
    std::cout << description << " in tv mode (4x3 aspect ratio)" << std::endl;
}

std::string Projector::toString() {
    return description;
}

void Projector::clear() {
    dvdPlayer = nullptr;
}
