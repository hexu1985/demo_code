#ifndef __statistics_display_h
#define __statistics_display_h

#include <iostream>
#include "display_element.h"
#include "observer.h"
#include "subject.h"

class Statistics_display: public Observer, public Display_element {
private:
    float max_temp = 0.0f;
    float min_temp = 200;
    float temp_sum = 0.0f;
    int num_readings = 0;

    Subject *weather_data;

public:
    Statistics_display(Subject *weather_data) {
        this->weather_data = weather_data;
        weather_data->register_observer(this);
    }

    ~Statistics_display() {
        weather_data->remove_observer(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        temp_sum += temperature;
        num_readings++;

        if (temperature > max_temp) {
            max_temp = temperature;
        }

        if (temperature < min_temp) {
            min_temp = temperature;
        }

        display();
    }

    void display() override {
        std::cout << "Avg/Max/Min temperature = " << (temp_sum / num_readings) << "/" << max_temp << "/" << min_temp << std::endl;
    }
};

#endif


