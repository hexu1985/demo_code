#include <stdio.h>
#include <time.h>    /* defines 'extern long timezone' */

int main(int argc, char **argv)
{
    time_t t, lt, gt;
    struct tm tm;

    t = time(NULL);
    lt = mktime(localtime(&t));
    gt = mktime(gmtime(&t));

    printf( "(t = time(NULL)) == %x,\n"
            "mktime(localtime(&t)) == %x,\n"
            "mktime(gmtime(&t)) == %x\n"
            "difftime(...) == %f\n"
            "timezone == %d\n", t, lt, gt,
            difftime(gt, lt), timezone);
    return 0;
}
