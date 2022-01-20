#include <stdio.h>
#include <time.h>    /* defines 'extern long timezone' */
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

time_t get_gmt_time_offset_impl(time_t local_time, const char* time_zone)
{
    std::cout << "get_gmt_time_offset_impl(" << local_time << ", " << time_zone << ")" << std::endl;
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

    return diff;
}

bool get_gmt_time_offset(time_t local_time, const char* time_zone, time_t *result)
{
    std::cout << "get_gmt_time_offset(" << local_time << ", " << time_zone << ")" << std::endl;

    int pipefd[2];
    pid_t cpid;
    time_t tbuf;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return false;
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        return false;
    }

    if (cpid == 0) {    /* Child reads from pipe */
        close(pipefd[0]);          /* Close unused read end */

        tbuf = get_gmt_time_offset_impl(local_time, time_zone);
        write(pipefd[1], &tbuf, sizeof(time_t));
        close(pipefd[1]);          /* Reader will see EOF */

        exit(0);
    } else {            /* Parent writes argv[1] to pipe */
        close(pipefd[1]);          /* Close unused write end */

        if (read(pipefd[0], (char *) &tbuf, sizeof(time_t)) <= 0) {
            perror("read from pipe");
            return false;
        }

        close(pipefd[0]);
        wait(NULL);                /* Wait for child */
        *result = tbuf;
    }

    std::cout << "get_gmt_time_offset(" << local_time << ", " << time_zone << "), result: " << *result << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    time_t t;
    bool ret;

    if (argc < 2) {
        ret = get_gmt_time_offset(time(NULL), "Asia/Shanghai", &t);
        assert(ret);

        ret = get_gmt_time_offset(time(NULL), "America/New_York", &t);
        assert(ret);
    }

    for (int i = 1; i < argc; i++) {
        ret = get_gmt_time_offset(time(NULL), argv[i], &t);
        assert(ret);
    }

    return 0;
}
