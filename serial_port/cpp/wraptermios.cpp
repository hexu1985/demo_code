#include <sys/ioctl.h>
#include "wraptermios.h"
#include "error.h"

#include <fcntl.h>

int Tty_open(const char *dev, int oflag)
{
    //dev 就是设备，设备就是文件，就是给出该设备文件的路径
    int fd = open(dev, oflag); // O_RDWR | O_NOCTTY | O_NDELAY
    if (-1 == fd) {
       err_sys("Can't open tty: %s with flag: %d", dev, oflag);
    }
    return fd;
}

int Tty_open_easy(const char *dev)
{
    return Tty_open(dev, O_RDWR | O_NOCTTY);
}

namespace {

static int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1800, B1200, B600,   
                           B300,   B200,   B150,  B134,  B110,  B75,   B50 };

static int name_arr[] = {  38400,  19200,  9600,  4800,  2400,  1800,  1200,  600, 
                           300,    200,    150,   134,   110,   75,    50, };

}   // namespace

void Tcgetattr(int fd, struct termios *termptr)
{
    if (tcgetattr(fd, termptr) < 0) {
       err_sys("tcgetattr error");
    }
}

void Tcsetattr(int fd, int opt, const struct termios *termptr)
{
    if (tcsetattr(fd, opt, termptr) < 0) {
       err_sys("tcsetattr error");
    }
}

void Tcflush(int fd, int queue)
{
    if (tcflush(fd, queue) < 0) {
        err_sys("tcflush error");
    }
}

void Cfsetispeed(struct termios *termptr, speed_t speed)
{
    if (cfsetispeed(termptr, speed) < 0) {
        err_sys("cfsetispeed error");
    }
}

void Cfsetospeed(struct termios *termptr, speed_t speed)
{
    if (cfsetospeed(termptr, speed) < 0) {
        err_sys("cfsetospeed error");
    }
}

void Tty_set_speed(int fd, int speed)
{
    size_t   i;
    struct termios   term;
    Tcgetattr(fd, &term);

    for (i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) {
        if  (speed == name_arr[i]) {
            /**
             * tcflush函数刷清(抛弃)输入缓存(终端驱动程序已接收到，但用户程序尚未读)或输出缓存(用户程序已经写，但尚未发送)。queue参数应是下列三个常数之一：
             * TCIFLUSH刷清输入队列。
             * TCOFLUSH刷清输出队列。
             * TCIOFLUSH刷清输入、输出队列。
*/
            Tcflush(fd, TCIOFLUSH); //设置前flush    
            Cfsetispeed(&term, speed_arr[i]);
            Cfsetospeed(&term, speed_arr[i]);

            //通过tcsetattr函数把新的属性设置到串口上。
            //tcsetattr(串口描述符，立即使用或者其他标示，指向termios的指针)
            Tcsetattr(fd, TCSANOW, &term);

            Tcflush(fd,TCIOFLUSH);  //设置后flush
            return;
        } 
    }

    err_quit("Tty_set_speed, invalid speed: %d", speed);
}

/**
 *@brief   设置串口数据位，停止位和效验位
 *@param  fd     类型  int  打开的串口文件句柄
 *@param  databits 类型  int 数据位   取值为 7 或者8
 *@param  stopbits 类型  int 停止位   取值为 1 或者2
 *@param  parity  类型  int  效验类型 取值为N,E,O,,S
 */
void Tty_set_parity(int fd, int databits, int stopbits, int parity)
{
    struct termios term;
    Tcgetattr(fd, &term);

    term.c_cflag &= ~CSIZE;
    switch (databits) /*设置数据位数*/
    {
    case 5:
       term.c_cflag |= CS5;
       break;
    case 6:
       term.c_cflag |= CS6;
       break;
    case 7:
       term.c_cflag |= CS7;
       break;
    case 8:
       term.c_cflag |= CS8;
       break;
    default:
       err_quit("Tty_set_parity, unsupported data size: %d", databits);
    }

    switch (parity)
    {
    case 'n':
    case 'N':
       term.c_cflag &= ~PARENB; /* Clear parity enable */
       term.c_iflag &= ~INPCK; /* Enable parity checking */
       break;
    case 'o':
    case 'O':
       term.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
       term.c_iflag |= INPCK; /* Disnable parity checking */
       break;
    case 'e':
    case 'E':
       term.c_cflag |= PARENB; /* Enable parity */
       term.c_cflag &= ~PARODD; /* 转换为偶效验*/
       term.c_iflag |= INPCK; /* Disnable parity checking */
       break;
    case 'S':
    case 's': /*as no parity*/
       term.c_cflag &= ~PARENB;
       term.c_cflag &= ~CSTOPB;
       break;
    default:
       err_quit("Tty_set_parity, unsupported parity: %d", parity);
    }

    /* 设置停止位*/
    switch (stopbits)
    {
    case 1:
       term.c_cflag &= ~CSTOPB;
       break;
    case 2:
       term.c_cflag |= CSTOPB;
       break;
    default:
       err_quit("Tty_set_parity, unsupported stop bits: %d", stopbits);
    }

    /* Set input parity option */
    if (parity != 'n')
       term.c_iflag |= INPCK;

    Tcsetattr(fd, TCSANOW, &term);
    Tcflush(fd,TCIOFLUSH);  //设置后flush
}

void Tty_set_icanon(int fd, int echo, int icanon)
{
    struct termios term;
    Tcgetattr(fd, &term);

    if (echo) {
        term.c_lflag |= ECHO;
    } else {
        term.c_lflag &= ~ECHO;
    }

    if (icanon) {
        term.c_lflag |= ICANON;
    } else {
        term.c_lflag &= ~ICANON;
    }

    Tcsetattr(fd, TCSANOW, &term);
    Tcflush(fd,TCIOFLUSH);  //设置后flush
}

void Tty_set_timeout(int fd, int min, int sec, int millisec)
{
    struct termios term;
    Tcgetattr(fd, &term);

    term.c_cc[VMIN] = min;
    term.c_cc[VTIME] = sec*10+millisec/100;

    Tcsetattr(fd, TCSANOW, &term);
    Tcflush(fd,TCIOFLUSH);  //设置后flush
}

namespace {

int
Ioctl(int fd, int request, void *arg)
{
	int		n;

	if ( (n = ioctl(fd, request, arg)) == -1)
		err_sys("ioctl error");
	return(n);	/* streamio of I_LIST returns value */
}

}

int Tty_get_modem_status(int fd)
{
	unsigned long serial;

    Ioctl(fd, TIOCMGET, &serial);
    return serial;
}

bool is_modem_status_dsr(int serial)
{
    return (serial & TIOCM_DSR);
}

void set_modem_status_dsr(int &serial, bool is_set)
{
    if (is_set) {
        serial = serial | TIOCM_DSR;
    } else {
        serial = serial & ~TIOCM_DSR;
    }
}

void unset_modem_status_dsr(int &serial)
{
    set_modem_status_dsr(serial, false);
}

void Tty_set_modem_status(int fd, int serial) 
{
    Ioctl(fd, TIOCMSET, &serial);
}

