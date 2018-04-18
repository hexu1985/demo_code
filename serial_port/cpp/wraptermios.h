#ifndef __wraptermios_h
#define __wraptermios_h

#include <termios.h>

int Tty_open(const char *dev, int oflag);
int Tty_open_easy(const char *dev);
void Tty_set_speed(int fd, int speed);
void Tty_set_parity(int fd, int databits, int stopbits, int parity);
void Tty_set_icanon(int fd, int echo, int icanon);
void Tty_set_timeout(int fd, int min, int sec, int millisec);

int Tty_get_modem_status(int fd);
void Tty_set_modem_status(int fd, int serial);

// bool TTY_MODEM_STATUS_LE(int serial);
// bool TTY_MODEM_STATUS_DTR(int serial);
// bool TTY_MODEM_STATUS_RTS(int serial);
// bool TTY_MODEM_STATUS_ST(int serial);
// bool TTY_MODEM_STATUS_SR(int serial);
bool TTY_MODEM_STATUS_CTS(int serial);
// bool TTY_MODEM_STATUS_CAR(int serial);
bool TTY_MODEM_STATUS_DCD(int serial);
bool TTY_MODEM_STATUS_CD(int serial);
// bool TTY_MODEM_STATUS_RNG(int serial);
bool TTY_MODEM_STATUS_RI(int serial);
bool TTY_MODEM_STATUS_DSR(int serial);

// void TTY_MODEM_STATUS_LE(int &serial, bool on);
// void TTY_MODEM_STATUS_DTR(int &serial, bool on);
// void TTY_MODEM_STATUS_RTS(int &serial, bool on);
// void TTY_MODEM_STATUS_ST(int &serial, bool on);
// void TTY_MODEM_STATUS_SR(int &serial, bool on);
// void TTY_MODEM_STATUS_CTS(int &serial, bool on);
// void TTY_MODEM_STATUS_CAR(int &serial, bool on);
// void TTY_MODEM_STATUS_CD(int &serial, bool on);
// void TTY_MODEM_STATUS_RNG(int &serial, bool on);
// void TTY_MODEM_STATUS_RI(int &serial, bool on);
void TTY_MODEM_STATUS_DSR(int &serial, bool on);

#endif
