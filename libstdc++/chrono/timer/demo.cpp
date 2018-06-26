// steady_clock example
#include <iostream>
#include <ctime>
#include "chrono_timer.h"
#include "chrono_util.h"

int main ()
{
  ChronoTimer timer;
  timer.start();

  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
  std::cout << std::endl;

  timer.stop();

  auto time_span = timer.elapsed();

  double nseconds = double(time_span.count()) * ChronoTimer::clock_type::period::num / ChronoTimer::clock_type::period::den;

  std::cout << "It took me " << nseconds << " seconds." << '\n';
  std::cout << "It took me " << duration_to_seconds(time_span) << " seconds." << '\n';
  std::cout << "It took me " << duration_to_milliseconds(time_span) << " milliseconds." << '\n';
  std::cout << "It took me " << duration_to_microseconds(time_span) << " microseconds." << '\n';
  std::cout << std::endl;

  return 0;
}

/*
Possible output:
printing out 1000 stars...
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
****************************************
It took me 0.084003 seconds.
*/
