#include "set_parity.h"
#include <termios.h>
#include <stdio.h>

/**
 *@brief   设置串口数据位，停止位和效验位
 *@param  fd     类型  int  打开的串口文件句柄
 *@param  databits 类型  int 数据位   取值为 7 或者8
 *@param  stopbits 类型  int 停止位   取值为 1 或者2
 *@param  parity  类型  int  效验类型 取值为N,E,O,,S
 */
int set_parity(int fd, int databits, int stopbits, int parity)
{
    struct termios options;
    if (tcgetattr(fd, &options) != 0)
    {
       perror("SetupSerial 1");
       return -1;
    }

    options.c_cflag &= ~CSIZE;
    switch (databits) /*设置数据位数*/
    {
    case 7:
       options.c_cflag |= CS7;
       break;
    case 8:
       options.c_cflag |= CS8;
       break;
    default:
       fprintf(stderr,"Unsupported data size\n");
       return -1;
    }

    switch (parity)
    {
    case 'n':
    case 'N':
       options.c_cflag &= ~PARENB; /* Clear parity enable */
       options.c_iflag &= ~INPCK; /* Enable parity checking */
       break;
    case 'o':
    case 'O':
       options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
       options.c_iflag |= INPCK; /* Disnable parity checking */
       break;
    case 'e':
    case 'E':
       options.c_cflag |= PARENB; /* Enable parity */
       options.c_cflag &= ~PARODD; /* 转换为偶效验*/
       options.c_iflag |= INPCK; /* Disnable parity checking */
       break;
    case 'S':
    case 's': /*as no parity*/
       options.c_cflag &= ~PARENB;
       options.c_cflag &= ~CSTOPB;
       break;
    default:
       fprintf(stderr,"Unsupported parity\n");
       return -1;
    }

    /* 设置停止位*/
    switch (stopbits)
    {
    case 1:
       options.c_cflag &= ~CSTOPB;
       break;
    case 2:
       options.c_cflag |= CSTOPB;
       break;
    default:
       fprintf(stderr,"Unsupported stop bits\n");
       return -1;
    }

    /* Set input parity option */
    if (parity != 'n')
       options.c_iflag |= INPCK;
    tcflush(fd, TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
       perror("SetupSerial 3");
       return -1;
    }
    return 0;
}
