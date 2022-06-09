#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
	const char* dev = "/dev/video0";
    if (argc > 1) {
        dev = argv[1];
    }
    int fd = open(dev,O_RDWR);

    printf("try open %s\n", dev);

    if (fd < 0)
    {
        perror("打开设备失败");
        return -1;
    } else {
        printf("打开设备成功\n");
    }

    close(fd);
    return 0;
}

