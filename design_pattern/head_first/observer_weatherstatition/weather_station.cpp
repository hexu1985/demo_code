#include <iostream>
#include <iomanip>
#include "weather_data.h"
#include "current_conditions_display.h"
#include "forecast_display.h"
#include "statistics_display.h"

int main(int argc, char *argv[])
{
    std::cout << std::fixed << std::setprecision(1);
    WeatherData weatherData;

    CurrentConditionsDisplay currentDisplay(&weatherData);
    StatisticsDisplay statisticsDisplay(&weatherData);
    ForecastDisplay forecastDisplayi(&weatherData);

    weatherData.setMeasurements(80, 65, 30.4f);
    weatherData.setMeasurements(82, 70, 29.2f);
    weatherData.setMeasurements(78, 90, 29.2f);
}

