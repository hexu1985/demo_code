#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void func()
{
    std::cerr << __func__ << ", in\n";
    std::cerr << __func__ << ", thread id: " << (long long) pthread_self() << "\n";
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        std::cerr << ".";
    }
    std::cerr << __func__ << ", exit\n";
}

int main(int argc, char *argv[])
{
    thread thr(func);
    this_thread::sleep_for(chrono::seconds(10));

    std::cerr << __func__ << ", thread id: " << thr.native_handle() << "\n";
    pthread_cancel(thr.native_handle());

    thr.join();
    return 0;
}
