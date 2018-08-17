#include <iostream>
#include <future>
#include <thread>
 
int main()
{
    using namespace std::chrono_literals;
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread([&p] {
          std::this_thread::sleep_for(1s);
          p.set_value_at_thread_exit(9);
    }).detach();
 
    std::cout << "Waiting..." << std::flush;
    f.wait();
    std::cout << "Done!\nResult is: " << f.get() << '\n';
}

/*
Output:

Waiting...Done!
Result is: 9
*/
