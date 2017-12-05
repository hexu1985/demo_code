#ifndef __statistics_display_h
#define __statistics_display_h

#include <iostream>
#include "display_element.h"
#include "observer.h"
#include "subject.h"

class StatisticsDisplay: public Observer, public DisplayElement {
private:
    float maxTemp = 0.0f;
    float minTemp = 200;
    float tempSum = 0.0f;
    int numReadings = 0;

    Subject *weatherData;

public:
    StatisticsDisplay(Subject *weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }

    ~StatisticsDisplay() {
        weatherData->removeObserver(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        tempSum += temperature;
        numReadings++;

        if (temperature > maxTemp) {
            maxTemp = temperature;
        }

        if (temperature < minTemp) {
            minTemp = temperature;
        }

        display();
    }

    void display() override {
        std::cout << "Avg/Max/Min temperature = " << (tempSum / numReadings) << "/" << maxTemp << "/" << minTemp << std::endl;
    }
};

#endif


