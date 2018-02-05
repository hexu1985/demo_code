#ifndef __ZHELPERS_S_SLEEP_HPP_INCLUDED__
#define __ZHELPERS_S_SLEEP_HPP_INCLUDED__

#include <time.h>

//  Sleep for a number of milliseconds
static void
s_sleep (int msecs)
{
    struct timespec t;
    t.tv_sec  =  msecs / 1000;
    t.tv_nsec = (msecs % 1000) * 1000000;
    nanosleep (&t, NULL);
}

#endif
