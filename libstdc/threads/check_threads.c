#include <stdio.h>

int main()
{
#ifdef __STDC_NO_THREADS__
    printf("no threads\n");
#else
    printf("have threads\n");
#endif

    return 0;
}

