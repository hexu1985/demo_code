#ifndef __current_conditions_display_h
#define __current_conditions_display_h

#include <iostream>
#include "display_element.h"
#include "observer.h"
#include "subject.h"

class Current_conditions_display: public Observer, public Display_element {
private:
    float temperature;
    float humidity;

    Subject *weather_data;

public:
    Current_conditions_display(Subject *weather_data) {
        this->weather_data = weather_data;
        weather_data->register_observer(this);
    }

    ~Current_conditions_display() {
        weather_data->remove_observer(this);
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
