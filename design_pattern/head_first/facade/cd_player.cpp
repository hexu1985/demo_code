#include "cd_player.h"
#include "amplifier.h"
#include <iostream>

CdPlayer::CdPlayer(std::string description, std::shared_ptr<Amplifier> amplifier) {
    std::cout << "create CdPlayer: " << description << std::endl;
    this->description = description;
    this->amplifier = amplifier;
}

CdPlayer::~CdPlayer() {
    std::cout << "destroy CdPlayer: " << description << std::endl;
}

void CdPlayer::on() {
    std::cout << description << " on" << std::endl;
}

void CdPlayer::off() {
    std::cout << description << " off" << std::endl;
}

void CdPlayer::eject() {
    title = "";
    std::cout << description << " eject" << std::endl;
}

void CdPlayer::play(std::string title) {
    this->title = title;
    currentTrack = 0;
    std::cout << description << " playing \"" << title << "\"" << std::endl;
}

void CdPlayer::play(int track) {
    if (title.empty()) {
        std::cout << description << " can't play track " << currentTrack << 
            ", no cd inserted" << std::endl;
    } else {
        currentTrack = track;
        std::cout << description << " playing track " << currentTrack << std::endl;
    }
}

void CdPlayer::stop() {
    currentTrack = 0;
    std::cout << description << " stopped" << std::endl;
}

void CdPlayer::clear() {
    amplifier = nullptr;
}

