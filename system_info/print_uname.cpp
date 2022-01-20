#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    struct utsname uts;
    if (uname(&uts) < 0) {
        perror("uname error");
        exit(1);
    }

    printf("sysname: %s, \nnodename: %s, \nrelease: %s, \nversion: %s, \nmachine: %s,\n",
            uts.sysname, uts.nodename, uts.release, uts.version, uts.machine);

    return 0;
}
