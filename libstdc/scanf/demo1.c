#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    const char *stat_str = "22138 (bash) S 22137 22138 22138 34817 32507 4194304 28811 372286 0 2 50 13 830 194 20 0 1 0 586250961 31735808"
        " 1594 18446744073709551615 94776653406208 94776654468104 140726993227248 0 0 0 65536 3670020 1266777851 1 0 0 17 3 0 0 0 0 0 94776656567696"
        " 94776656614756 94776670384128 140726993235424 140726993235430 140726993235430 140726993235950 0";

    int tid = 0;
    char name[128];
    uint32_t utime = 0, stime = 0, cutime = 0, cstime = 0;
    sscanf(stat_str, "%d (%[^)]%*s %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %u %u %u %u",
                    &tid, name, &utime, &stime, &cutime, &cstime);

    printf("tid: %d\n", tid);
    printf("name: %s\n", name);
    printf("utime: %u\n", utime);
    printf("stime: %u\n", stime);
    printf("cutime: %u\n", cutime);
    printf("cstime: %u\n", cstime);

    return 0;
}

