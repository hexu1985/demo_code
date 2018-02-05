#ifndef __ZHELPERS_S_CLOCK_H_INCLUDED__
#define __ZHELPERS_S_CLOCK_H_INCLUDED__

#include <sys/time.h>

//  Return current system clock as milliseconds
static int64_t
s_clock (void)
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

#endif
