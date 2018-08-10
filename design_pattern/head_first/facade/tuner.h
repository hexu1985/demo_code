#ifndef __tuner_h
#define __tuner_h

#include <string>
#include <memory>

class Amplifier;

class Tuner {
private:
    std::string description;
    std::shared_ptr<Amplifier> amplifier;
    double frequency;

public:
    Tuner(std::string description, std::shared_ptr<Amplifier> amplifier);

    ~Tuner();

    void on();

    void off();

    void setFrequency(double frequency);

    void setAm();

    void setFm();

    std::string toString();

    void clear();
};

#endif
