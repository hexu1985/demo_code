#ifndef __cd_player_h
#define __cd_player_h

#include <string>
#include <memory>

class Amplifier; 

class CdPlayer {
private:
	std::string description;
	int currentTrack;
    std::shared_ptr<Amplifier> amplifier;
	std::string title;

public:    
	CdPlayer(std::string description, std::shared_ptr<Amplifier> amplifier);

	~CdPlayer();
 
	void on();
 
	void off();

	void eject();
 
	void play(std::string title);

	void play(int track);

	void stop();
 
	void pause();
 
	std::string toString();

    void clear();
};

#endif
