#ifndef __forecast_display_h
#define __forecast_display_h

#include <iostream>
#include "display_element.h"
#include "observer.h"
#include "subject.h"

class Forecast_display: public Observer, public Display_element {
private:
    float current_pressure = 29.92f;
    float last_pressure;

    Subject *weather_data;

public:
    Forecast_display(Subject *weather_data) {
        this->weather_data = weather_data;
        weather_data->register_observer(this);
    }

    ~Forecast_display() {
        weather_data->remove_observer(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        last_pressure = current_pressure;
        current_pressure = pressure;
        display();
    }

    void display() override {
        std::cout << "Forecast: ";
        if (current_pressure > last_pressure) {
            std::cout << "Improving weather on the way!" << std::endl;
        } else if (current_pressure == last_pressure) {
            std::cout << "More of the same" << std::endl;
        } else if (current_pressure < last_pressure) {
            std::cout << "Watch out for cooler, rainy weather" << std::endl;
        }
    }
};

#endif

