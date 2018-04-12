#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "open_dev.h"
#include "set_speed.h"
#include "set_parity.h"

int main(int argc, char **argv)
{
    int fd;
    int nread;
    char buff[512];
    const char *dev = "/dev/tty"; 
    int baud_rate = 38400;

    if (argc != 3) 
    {
        printf("usage: %s <dev> <baud rate>\n", argv[0]);
        exit(1);
    }
    dev = argv[1];
    baud_rate = atoi(argv[2]);

    fd = open_dev(dev);
    if (fd < 0) {
        printf("open dev '%s' failed!\n", dev);
        exit(1);
    }

    set_speed(fd, baud_rate);
    if (set_parity(fd, 8, 1, 'N') < 0)
    {
       printf("Set Parity Error\n");
       exit (1);
    }

    while (1) //循环读取数据
    {
       while ((nread = read(fd, buff, 512))>0)
       {
//           printf("\nLen %d\n", nread);
           buff[nread+1] = '\0';
           fprintf(stderr, "%s", buff);
       }
    }

    close(fd); 
    return 0;
}
