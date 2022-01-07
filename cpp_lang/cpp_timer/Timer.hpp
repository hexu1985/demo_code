#include <atomic>
#include <thread>
#include <chrono>
#include <functional>

class Timer {
public:
	typedef std::function<void ()> Callback;

	template <class Rep, class Period>
    void setTimeoutFor(Callback function, const std::chrono::duration<Rep, Period> &delay);

	template <class Clock, class Duration>
	void setTimeoutUntil(Callback function, const std::chrono::time_point<Clock, Duration> &delay);

	template <class Rep, class Period>
    void setInterval(Callback function, const std::chrono::duration<Rep, Period> &interval);

    void stop();

	Timer() = default; 
	~Timer() = default; 

private:
	std::atomic<bool> clear_{false};
};

template <class Rep, class Period>
void Timer::setTimeoutFor(Callback function, const std::chrono::duration<Rep, Period> &delay) 
{
    this->clear_ = false;
    std::thread t([=]() {
        if(this->clear_) return;
        std::this_thread::sleep_for(delay);
        if(this->clear_) return;
        function();
    });
    t.detach();
}

template <class Clock, class Duration>
void Timer::setTimeoutUntil(Callback function, const std::chrono::time_point<Clock, Duration> &delay)
{
    this->clear_ = false;
    std::thread t([=]() {
        if(this->clear_) return;
        std::this_thread::sleep_until(delay);
        if(this->clear_) return;
        function();
    });
    t.detach();
}

template <class Rep, class Period>
void Timer::setInterval(Callback function, const std::chrono::duration<Rep, Period> &interval)
{
    this->clear_ = false;
    std::thread t([=]() {
        while(true) {
            if(this->clear_) return;
            std::this_thread::sleep_for(interval);
            if(this->clear_) return;
            function();
        }
    });
    t.detach();
}

void Timer::stop() 
{
    this->clear_ = true;
}
