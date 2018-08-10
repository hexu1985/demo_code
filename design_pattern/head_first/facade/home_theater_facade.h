#ifndef __home_theater_facade_h
#define __home_theater_facade_h

#include <memory>
#include <string>
#include "amplifier.h"
#include "cd_player.h"
#include "dvd_player.h"
#include "popcorn_popper.h"
#include "projector.h"
#include "screen.h"
#include "theater_lights.h"
#include "tuner.h"

class HomeTheaterFacade {
private:
	std::shared_ptr<Amplifier> amp;
	std::shared_ptr<Tuner> tuner;
	std::shared_ptr<DvdPlayer> dvd;
	std::shared_ptr<CdPlayer> cd;
	std::shared_ptr<Projector> projector;
	std::shared_ptr<TheaterLights> lights;
	std::shared_ptr<Screen> screen;
	std::shared_ptr<PopcornPopper> popper;
 
public:
	HomeTheaterFacade(std::shared_ptr<Amplifier> amp, 
				 std::shared_ptr<Tuner> tuner, 
				 std::shared_ptr<DvdPlayer> dvd, 
				 std::shared_ptr<CdPlayer> cd, 
				 std::shared_ptr<Projector> projector, 
				 std::shared_ptr<Screen> screen,
				 std::shared_ptr<TheaterLights> lights,
				 std::shared_ptr<PopcornPopper> popper); 

    ~HomeTheaterFacade();
 
	void watchMovie(std::string movie);
 
	void endMovie();

	void listenToCd(std::string cdTitle);

	void endCd();

	void listenToRadio(double frequency);

	void endRadio();
};

#endif
