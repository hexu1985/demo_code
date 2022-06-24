#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
