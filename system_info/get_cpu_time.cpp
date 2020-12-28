#include <sys/times.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    int n = 10000;
    if (argc > 1)
        n = std::stoi(argv[1]);
    
    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += ((double) i) * ((double) i);
    }
    std::cout << "sum: " << sum << std::endl;

    struct tms curr_tms;
    auto wall_clk = times(&curr_tms);
    std::cout << "wall_clk: " << wall_clk << std::endl;
    std::cout << "tms_utime: " << curr_tms.tms_utime << std::endl;
    std::cout << "tms_stime: " << curr_tms.tms_stime << std::endl;

    return 0;
}
