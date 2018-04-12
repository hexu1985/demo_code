#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int open_dev(const char *dev)
{
    //dev 就是设备，设备就是文件，就是给出该设备文件的路径
    int fd = open(dev, O_RDWR ); //| O_NOCTTY | O_NDELAY
    if (-1 == fd)
    {
       perror("Can't Open Serial Port");
       return -1;
    }
    else
       return fd;
}
