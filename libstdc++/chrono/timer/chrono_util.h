#ifndef __chrono_util_h
#define __chrono_util_h

#include <chrono>

template <typename Rep, typename Period>
double duration_to_seconds(const std::chrono::duration<Rep, Period> &dtn)
{
    return double(Period::num)/Period::den * dtn.count();
}

template <typename Rep, typename Period>
double duration_to_milliseconds(const std::chrono::duration<Rep, Period> &dtn)
{
    return double(Period::num)*1000/Period::den * dtn.count();
}

template <typename Rep, typename Period>
double duration_to_microseconds(const std::chrono::duration<Rep, Period> &dtn)
{
    return double(Period::num)*1000000/Period::den * dtn.count();
}

#endif
