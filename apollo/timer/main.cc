#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "cyber/cyber.h"
#include "cyber/init.h"

int main(int argc, char** argv) {
    ::apollo::cyber::Init(argv[0]);
    // Print current time every 1s
    ::apollo::cyber::Timer timer(1000, [](){
        std::time_t tt = time(0);
        std::cout << ctime(&tt) << std::endl;
    }, false);
    timer.Start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    timer.Stop();
}
