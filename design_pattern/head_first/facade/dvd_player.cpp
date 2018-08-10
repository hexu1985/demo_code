#include "dvd_player.h"
#include <iostream>

DvdPlayer::DvdPlayer(std::string description, std::shared_ptr<Amplifier> amplifier) {
    std::cout << "create DvdPlayer: " << description << std::endl;
    this->description = description;
    this->amplifier = amplifier;
}

DvdPlayer::~DvdPlayer() {
    std::cout << "destroy DvdPlayer: " << description << std::endl;
}

void DvdPlayer::on() {
    std::cout << description << " on" << std::endl;
}

void DvdPlayer::off() {
    std::cout << description << " off" << std::endl;
}

void DvdPlayer::eject() {
    movie = "";
    std::cout << description << " eject" << std::endl;
}

void DvdPlayer::play(std::string movie) {
    this->movie = movie;
    currentTrack = 0;
    std::cout << description << " playing \"" << movie << "\"" << std::endl;
}

void DvdPlayer::play(int track) {
    if (movie.empty()) {
        std::cout << description << " can't play track " << track << " no dvd inserted" << std::endl;
    } else {
        currentTrack = track;
        std::cout << description << " playing track " << currentTrack << " of \"" << movie << "\"" << std::endl;
    }
}

void DvdPlayer::stop() {
    currentTrack = 0;
    std::cout << description << " stopped \"" << movie << "\"" << std::endl;
}

void DvdPlayer::pause() {
    std::cout << description << " paused \"" << movie << "\"" << std::endl;
}

void DvdPlayer::setTwoChannelAudio() {
    std::cout << description << " set two channel audio" << std::endl;
}

void DvdPlayer::setSurroundAudio() {
    std::cout << description << " set surround audio" << std::endl;
}

std::string DvdPlayer::toString() {
    return description;
}

void DvdPlayer::clear() {
    amplifier = nullptr;
}

