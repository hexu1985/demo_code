#ifndef __chrono_timer_h
#define __chrono_timer_h

#include <chrono>

class ChronoTimer {
public:
    typedef std::chrono::steady_clock clock_type;
    typedef clock_type::time_point time_point;
    typedef clock_type::duration duration;

    ChronoTimer() = default;

    void start()
    {
        start_ = clock_type::now();
    }

    void stop()
    {
        stop_ = clock_type::now();
    }

    duration elapsed()
    {
        return stop_ - start_;
    }

private:
    time_point start_;
    time_point stop_;
};

#endif
