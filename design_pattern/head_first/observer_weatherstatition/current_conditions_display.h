#ifndef __current_conditions_display_h
#define __current_conditions_display_h

#include <iostream>
#include "display_element.h"
#include "observer.h"
#include "subject.h"

class CurrentConditionsDisplay: public Observer, public DisplayElement {
private:
    float temperature;
    float humidity;

    Subject *weatherData;

public:
    CurrentConditionsDisplay(Subject *weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }

    ~CurrentConditionsDisplay() {
        weatherData->removeObserver(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display() override {
        std::cout << "Current conditions: " << temperature 
                << "F degrees and " << humidity << "% humidity" << std::endl;
    }
};

#endif
