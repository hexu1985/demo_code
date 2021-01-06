#include <sys/times.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    int n = 10000;
    if (argc > 1)
        n = std::stoi(argv[1]);
    
    struct tms begin_tms;
    clock_t begin_clk = times(&begin_tms);
    std::cout << "begin_clk: " << begin_clk << std::endl;
    std::cout << "tms_utime: " << begin_tms.tms_utime << std::endl;
    std::cout << "tms_stime: " << begin_tms.tms_stime << std::endl;

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += ((double) i) * ((double) i);
    }
    std::cout << "sum: " << sum << std::endl;

    sleep(1);

    struct tms curr_tms;
    clock_t curr_clk = times(&curr_tms);
    std::cout << "curr_clk: " << curr_clk << std::endl;
    std::cout << "tms_utime: " << curr_tms.tms_utime << std::endl;
    std::cout << "tms_stime: " << curr_tms.tms_stime << std::endl;

    double usage = (double) ((curr_tms.tms_utime - begin_tms.tms_utime)
                    + (curr_tms.tms_stime - begin_tms.tms_stime)) /
                    (double) (curr_clk - begin_clk);
    std::cout << "usage: " << usage*100 << "%" << std::endl;

    return 0;
}
