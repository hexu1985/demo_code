#include "home_theater_facade.h"

int main(int argc, char *argv[]) {
    auto amp = std::make_shared<Amplifier>("Top-O-Line Amplifier");
    auto tuner = std::make_shared<Tuner>("Top-O-Line AM/FM Tuner", amp);
    auto dvd = std::make_shared<DvdPlayer>("Top-O-Line DVD Player", amp);
    auto cd = std::make_shared<CdPlayer>("Top-O-Line CD Player", amp);
    auto projector = std::make_shared<Projector>("Top-O-Line Projector", dvd);
    auto lights = std::make_shared<TheaterLights>("Theater Ceiling Lights");
    auto screen = std::make_shared<Screen>("Theater Screen");
    auto popper = std::make_shared<PopcornPopper>("Popcorn Popper");

    HomeTheaterFacade homeTheater(amp, tuner, dvd, cd, 
            projector, screen, lights, popper);

    homeTheater.watchMovie("Raiders of the Lost Ark");
    homeTheater.endMovie();

    return 0;
}

