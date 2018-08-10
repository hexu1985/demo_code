#ifndef __ampliter_h
#define __ampliter_h

#include <memory>
#include <string>

class Tuner;
class DvdPlayer;
class CdPlayer;

class Amplifier {
private:
	std::string description;
	std::shared_ptr<Tuner> tuner;
	std::shared_ptr<DvdPlayer> dvd;
	std::shared_ptr<CdPlayer> cd;
	
public:
	Amplifier(std::string description); 

    ~Amplifier(); 
 
	void on();
 
	void off();
 
	void setStereoSound();
 
	void setSurroundSound();
 
	void setVolume(int level);

	void setTuner(std::shared_ptr<Tuner> tuner);
  
	void setDvd(std::shared_ptr<DvdPlayer> dvd);
 
	void setCd(std::shared_ptr<CdPlayer> cd);
 
	std::string toString();

    void clear(); 
};

#endif
