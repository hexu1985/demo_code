/* strftime example */
#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */
#include "boost/chrono.hpp"

int main ()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    using namespace boost::chrono;

    system_clock::time_point tp = system_clock::now();
    rawtime = system_clock::to_time_t(tp);

    timeinfo = gmtime (&rawtime);

    strftime (buffer,80,"%Y%m%d%H%M%S",timeinfo);
    puts (buffer);

    return 0;
}
