#ifndef __wraptermios_h
#define __wraptermios_h

#include <termios.h>

int Tty_open(const char *dev, int oflag);
int Tty_open_for_read(const char *dev);
int Tty_open_for_write(const char *dev);
void Tty_set_speed(int fd, int speed);
void Tty_set_parity(int fd, int databits, int stopbits, int parity);

#endif
