#ifndef __dvd_player_h
#define __dvd_player_h

#include <memory>
#include <string>

class Amplifier;

class DvdPlayer {
private:
    std::string description;
    int currentTrack;
    std::shared_ptr<Amplifier> amplifier;
    std::string movie;

public:
    DvdPlayer(std::string description, std::shared_ptr<Amplifier> amplifier);

    ~DvdPlayer();

    void on();

    void off();

    void eject();

    void play(std::string movie);

    void play(int track);

    void stop();

    void pause();

    void setTwoChannelAudio();

    void setSurroundAudio();

    std::string toString();

    void clear();
};

#endif
