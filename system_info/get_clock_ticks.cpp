#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
    const int32_t clock_ticks = sysconf(_SC_CLK_TCK);
    std::cout << "clock_ticks: " << clock_ticks << std::endl;

    return 0;
}
