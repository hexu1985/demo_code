#ifndef __weather_data_h
#define __weather_data_h

#include <list>
#include <algorithm>
#include "subject.h"
#include "observer.h"

class Weather_data: public Subject {
private:
    std::list<Observer *> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    Weather_data() {
    }

    void register_observer(Observer *o) override {
        observers.push_back(o);
    }

    void remove_observer(Observer *o) override {
        auto ret = std::find(observers.begin(), observers.end(), o);
        if (ret != observers.end())
            observers.erase(ret);
    }

    void notify_observers() override {
        for (auto &observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    void measurements_changed() {
        notify_observers();
    }

    void set_measurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurements_changed();
    }
};

#endif
