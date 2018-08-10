#include <iostream>
#include "home_theater_facade.h"

HomeTheaterFacade::HomeTheaterFacade(std::shared_ptr<Amplifier> amp, 
        std::shared_ptr<Tuner> tuner, 
        std::shared_ptr<DvdPlayer> dvd, 
        std::shared_ptr<CdPlayer> cd, 
        std::shared_ptr<Projector> projector, 
        std::shared_ptr<Screen> screen,
        std::shared_ptr<TheaterLights> lights,
        std::shared_ptr<PopcornPopper> popper) {

    std::cout << "create HomeTheaterFacade: " << std::endl;

    this->amp = amp;
    this->tuner = tuner;
    this->dvd = dvd;
    this->cd = cd;
    this->projector = projector;
    this->screen = screen;
    this->lights = lights;
    this->popper = popper;
}

HomeTheaterFacade::~HomeTheaterFacade() {
    std::cout << "destroy HomeTheaterFacade: " << std::endl;
    amp->clear();
    tuner->clear();
    dvd->clear();
    cd->clear();
    projector->clear();
    screen->clear();
    lights->clear();
    popper->clear();
}

void HomeTheaterFacade::watchMovie(std::string movie) {
    std::cout << "Get ready to watch a movie..." << std::endl;
    popper->on();
    popper->pop();
    lights->dim(10);
    screen->down();
    projector->on();
    projector->wideScreenMode();
    amp->on();
    amp->setDvd(dvd);
    amp->setSurroundSound();
    amp->setVolume(5);
    dvd->on();
    dvd->play(movie);
}


void HomeTheaterFacade::endMovie() {
    std::cout << "Shutting movie theater down..." << std::endl;
    popper->off();
    lights->on();
    screen->up();
    projector->off();
    amp->off();
    dvd->stop();
    dvd->eject();
    dvd->off();
}

void HomeTheaterFacade::listenToCd(std::string cdTitle) {
    std::cout << "Get ready for an audiopile experence..." << std::endl;
    lights->on();
    amp->on();
    amp->setVolume(5);
    amp->setCd(cd);
    amp->setStereoSound();
    cd->on();
    cd->play(cdTitle);
}

void HomeTheaterFacade::endCd() {
    std::cout << "Shutting down CD..." << std::endl;
    amp->off();
    amp->setCd(cd);
    cd->eject();
    cd->off();
}

void HomeTheaterFacade::listenToRadio(double frequency) {
    std::cout << "Tuning in the airwaves..." << std::endl;
    tuner->on();
    tuner->setFrequency(frequency);
    amp->on();
    amp->setVolume(5);
    amp->setTuner(tuner);
}

void HomeTheaterFacade::endRadio() {
    std::cout << "Shutting down the tuner..." << std::endl;
    tuner->off();
    amp->off();
}
