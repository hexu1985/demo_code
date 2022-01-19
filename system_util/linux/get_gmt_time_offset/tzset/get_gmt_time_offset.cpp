#include <stdio.h>
#include <time.h>    /* defines 'extern long timezone' */
#include <iostream>

time_t get_gmt_time_offset(time_t local_time, const char* time_zone)
{
    std::cout << "get_gmt_time_offset(" << local_time << ", " << time_zone << ")" << std::endl;
    time_t t, lt, gt;
    struct tm tm;

    char *ts_old = getenv("TZ");

    setenv("TZ", time_zone, 1);

    tzset();

    t = local_time;
    lt = mktime(localtime(&t));
    gt = mktime(gmtime(&t));

    time_t diff = static_cast<time_t>(difftime(gt, lt));

    printf( "(t = time(NULL)) == %x,\n"
            "mktime(localtime(&t)) == %x,\n"
            "mktime(gmtime(&t)) == %x\n"
            "difftime(...) == %f\n"
            "timezone == %d\n", t, lt, gt,
            difftime(gt, lt), timezone);

    if (ts_old) {
        setenv("TZ", ts_old, 1);
    } else {
        setenv("TZ", "", 1);
    }

    tzset();

    std::cout << std::endl;
    return diff;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        time_t t1 = get_gmt_time_offset(time(NULL), "Asia/Shanghai");
        time_t t2 = get_gmt_time_offset(time(NULL), "America/New_York");
    }

    for (int i = 1; i < argc; i++) {
        time_t t = get_gmt_time_offset(time(NULL), argv[i]);
    }

    return 0;
}
