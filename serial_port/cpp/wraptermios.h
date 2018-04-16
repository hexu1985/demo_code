#ifndef __wraptermios_h
#define __wraptermios_h

#include <termios.h>

int Tty_open(const char *dev, int oflag);
int Tty_open_easy(const char *dev);
void Tty_set_speed(int fd, int speed);
void Tty_set_parity(int fd, int databits, int stopbits, int parity);
void Tty_set_icanon(int fd, int echo, int icanon);
void Tty_set_timeout(int fd, int min, int sec, int millisec);

#endif
