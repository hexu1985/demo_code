#include <sys/time.h>
#include <stdio.h>

int main() {
    struct timeval current_time;
    struct timezone tz;
    gettimeofday(&current_time, &tz);
    printf("seconds : %ld\nmicro seconds : %ld\n",
            current_time.tv_sec, current_time.tv_usec);
    printf("minuteswest : %d\ndsttime : %d\n",
            tz.tz_minuteswest, tz.tz_dsttime);

    return 0;
}

