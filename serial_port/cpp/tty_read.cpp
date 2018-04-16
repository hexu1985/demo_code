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
    char *dev = "/dev/pts/2"; //串口二

    fd = open_dev(dev);
    set_speed(fd, 38400);
    if (set_parity(fd, 8, 1, 'N') < 0)
    {
       printf("Set Parity Error\n");
       exit (1);
    }

    while (1) //循环读取数据
    {
       while ((nread = read(fd, buff, 512))>0)
       {
           printf("\nLen %d\n", nread);
           buff[nread+1] = '\0';
           printf("\n%s", buff);
       }
    }

    close(fd); 
    return 0;
}
