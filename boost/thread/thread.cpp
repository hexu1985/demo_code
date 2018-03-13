#include <iostream>
#include <utility>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/ref.hpp>
 
void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 executing\n";
        ++n;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
    }
}
 
void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
    }
}
 
int main()
{
    int n = 0;
    boost::thread t1; // t1 is not a thread
    boost::thread t2(f1, n + 1); // pass by value
    boost::thread t3(f2, boost::ref(n)); // pass by reference
    t2.join();
    t3.join();
    std::cout << "Final value of n is " << n << '\n';
}
