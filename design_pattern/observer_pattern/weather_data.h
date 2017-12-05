#ifndef __weather_data_h
#define __weather_data_h

#include <list>
#include <algorithm>
#include "subject.h"
#include "observer.h"

class WeatherData: public Subject {
private:
    std::list<Observer *> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherData() {
    }

    void registerObserver(Observer *o) override {
        observers.push_back(o);
    }

    void removeObserver(Observer *o) override {
        auto ret = std::find(observers.begin(), observers.end(), o);
        if (ret != observers.end())
            observers.erase(ret);
    }

    void notifyObservers() override {
        for (auto &observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    void measurementsChanged() {
        notifyObservers();
    }

    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
};

#endif
