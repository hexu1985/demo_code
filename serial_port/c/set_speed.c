#include "set_speed.h"
#include <termios.h>
#include <stdio.h>

/**
 *@brief  设置串口通信速率
 *@param  fd     类型 int  打开串口的文件句柄
 *@param  speed  类型 int  串口速度
 *@return  void
*/

static int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1800, B1200, B600,   
                           B300,   B200,   B150,  B134,  B110,  B75,   B50 };

static int name_arr[] = {  38400,  19200,  9600,  4800,  2400,  1800,  1200,  600, 
                           300,    200,    150,   134,   110,   75,    50, };

int set_speed(int fd, int speed)
{
    int   i;
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);

    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) {
        if  (speed == name_arr[i]) {
            /**
             * tcflush函数刷清(抛弃)输入缓存(终端驱动程序已接收到，但用户程序尚未读)或输出缓存(用户程序已经写，但尚未发送)。queue参数应是下列三个常数之一：
             * TCIFLUSH刷清输入队列。
             * TCOFLUSH刷清输出队列。
             * TCIOFLUSH刷清输入、输出队列。
*/
            tcflush(fd, TCIOFLUSH);//设置前flush    
            cfsetispeed(&Opt, speed_arr[i]); 
            cfsetospeed(&Opt, speed_arr[i]);  

            //通过tcsetattr函数把新的属性设置到串口上。
            //tcsetattr(串口描述符，立即使用或者其他标示，指向termios的指针)
            status = tcsetattr(fd, TCSANOW, &Opt); 
            if  (status != 0)
            {       
                perror("tcsetattr fd1"); 
                return -1;    
            }   

            tcflush(fd,TCIOFLUSH);  //设置后flush
        } 
    }

    return 0;
}
