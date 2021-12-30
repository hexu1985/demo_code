#include <sys/times.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>

uint64_t get_cpu_use_jiffies(const char *proc_path) {
    FILE * pfile = fopen(proc_path, "r");
    if (!pfile) {
        std::cerr << "openfile: " << proc_path << " error\n";
        exit(1);
    }

    uint64_t utime = 0, stime = 0, cutime = 0, cstime = 0;
    fscanf(pfile, "%*d %*s %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %lu %lu %lu",
            &utime, &stime, &cutime, &cstime);

    uint64_t jiffies = utime + stime + cutime + cstime;

    fclose(pfile);

    return jiffies;
}

int main(int argc, char *argv[])
{
    int n = 10000;
    if (argc > 1)
        n = std::stoi(argv[1]);

    std::chrono::system_clock::time_point tp_beg = std::chrono::system_clock::now();

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += ((double) i) * ((double) i);
    }
    std::cout << "sum: " << sum << std::endl;

    sleep(1);

    std::chrono::system_clock::time_point tp_end = std::chrono::system_clock::now();
    uint64_t total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp_end-tp_beg).count();

    const int32_t clock_ticks = sysconf(_SC_CLK_TCK);
    std::cout << "clock_ticks: " << clock_ticks << std::endl;
    uint64_t cpu_use_jiffies = get_cpu_use_jiffies("/proc/self/stat");
    uint64_t cpu_use_ms = cpu_use_jiffies * (1000.0f / clock_ticks);

    std::cout << "total_ms: " << total_ms << std::endl;
    std::cout << "cpu_use_ms: " << cpu_use_ms << std::endl;
    double usage = cpu_use_ms / (double) total_ms;
    std::cout << "usage: " << usage*100 << "%" << std::endl;

    return 0;
}
