#ifndef __forecast_display_h
#define __forecast_display_h

#include <iostream>
#include "display_element.h"
#include "observer.h"
#include "subject.h"

class ForecastDisplay: public Observer, public DisplayElement {
private:
    float currentPressure = 29.92f;
    float lastPressure;

    Subject *weatherData;

public:
    ForecastDisplay(Subject *weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }

    ~ForecastDisplay() {
        weatherData->removeObserver(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        lastPressure = currentPressure;
        currentPressure = pressure;
        display();
    }

    void display() override {
        std::cout << "Forecast: ";
        if (currentPressure > lastPressure) {
            std::cout << "Improving weather on the way!" << std::endl;
        } else if (currentPressure == lastPressure) {
            std::cout << "More of the same" << std::endl;
        } else if (currentPressure < lastPressure) {
            std::cout << "Watch out for cooler, rainy weather" << std::endl;
        }
    }
};

#endif

