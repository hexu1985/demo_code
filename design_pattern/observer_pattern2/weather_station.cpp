#include <iostream>
#include <iomanip>
#include "weather_data.h"
#include "current_conditions_display.h"
#include "forecast_display.h"
#include "statistics_display.h"

int main(int argc, char *argv[])
{
    std::cout << std::fixed << std::setprecision(1);
    Weather_data weather_data;

    Current_conditions_display current_display(&weather_data);
    Statistics_display statistics_display(&weather_data);
    Forecast_display forecast_displayi(&weather_data);

    weather_data.set_measurements(80, 65, 30.4f);
    weather_data.set_measurements(82, 70, 29.2f);
    weather_data.set_measurements(78, 90, 29.2f);
}

