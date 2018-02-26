#include <thread>
#include <iostream>
#include "Poco/Timer.h"  
#include "Poco/Thread.h"  

using Poco::Timer;  
using Poco::TimerCallback;  
using Poco::Thread;  
  
class TimerExample  
{  
    public:  
    void onTimer(Poco::Timer& timer)  
    {  
        std::cout << "onTimer called." << " thread_id: " << std::this_thread::get_id() << std::endl;  
    }  
};  
  
int main(int argc, char** argv)  
{  
    TimerExample te;  
    Timer timer(250, 500); // fire after 250ms, repeat every 500ms  
    timer.start(TimerCallback<TimerExample>(te, &TimerExample::onTimer));  
    Thread::sleep(5000);  
    timer.stop();  
    return 0;  
} 

