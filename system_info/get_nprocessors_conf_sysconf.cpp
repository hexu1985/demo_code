#include <iostream>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    long n = sysconf(_SC_NPROCESSORS_CONF);
    if (n < 0) {
        std::cerr << "sysconf error!\n";
        exit(1);
    }

    std::cout << "processor count: " << n << std::endl;

    return 0;
}
