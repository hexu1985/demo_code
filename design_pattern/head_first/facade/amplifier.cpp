#include "amplifier.h"
#include "tuner.h"
#include "dvd_player.h"
#include "cd_player.h"
#include <iostream>

Amplifier::Amplifier(std::string description) {
    std::cout << "create Amplifier: " << description << std::endl;
    this->description = description;
}

Amplifier::~Amplifier() {
    std::cout << "destroy Amplifier: " << description << std::endl;
}

void Amplifier::on() {
    std::cout << description << " on" << std::endl;
}

void Amplifier::off() {
    std::cout << description << " off" << std::endl;
}

void Amplifier::setStereoSound() {
    std::cout << description << " stereo mode on" << std::endl;
}

void Amplifier::setSurroundSound() {
    std::cout << description << " surround sound on (5 speakers, 1 subwoofer)" << std::endl;
}

void Amplifier::setVolume(int level) {
    std::cout << description << " setting volume to " << level << std::endl;
}

void Amplifier::setTuner(std::shared_ptr<Tuner> tuner) {
    std::cout << description << " setting tuner to " << dvd << std::endl;
    this->tuner = tuner;
}

void Amplifier::setDvd(std::shared_ptr<DvdPlayer> dvd) {
    std::cout << description << " setting DVD player to " << dvd << std::endl;
    this->dvd = dvd;
}

void Amplifier::setCd(std::shared_ptr<CdPlayer> cd) {
    std::cout << description << " setting CD player to " << cd << std::endl;
    this->cd = cd;
}

std::string Amplifier::toString() {
    return description;
}

void Amplifier::clear() {
    tuner = nullptr;
    dvd = nullptr;
    cd = nullptr;
}

