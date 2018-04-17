#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "tty_reader.h"
#include "wraptermios.h"
#include "wrapsock.h"

TtyReader::TtyReader(): tty_fd_(-1)
{
}

TtyReader::~TtyReader()
{
    if (is_open())
        close();
}

void TtyReader::check_open() const
{
    if (!is_open())
        assert("tty is not open");
}

void TtyReader::open(const char *dev)
{
    this->open(dev, O_RDONLY | O_NOCTTY);
}

void TtyReader::open(const char *dev, int oflag)
{
    if (is_open())
        assert("tty is already opened");

    tty_fd_ = Tty_open(dev, oflag);
}

void TtyReader::close()
{
    if (is_open())
        return;
    ::close(tty_fd_);
}

void TtyReader::setSpeed(int speed)
{
    check_open();
    Tty_set_speed(tty_fd_, speed);
}

void TtyReader::setParity(int databits, int stopbits, int parity)
{
    check_open();
    Tty_set_parity(tty_fd_, databits, stopbits, parity);
}

void TtyReader::setIcanon(int echo, int icanon)
{
    check_open();
    Tty_set_icanon(tty_fd_, echo, icanon);
}

void TtyReader::setTimeout(int min, int sec, int millisec)
{
    check_open();
    Tty_set_timeout(tty_fd_, min, sec, millisec);
}

int TtyReader::read(char *buff, int size)
{
    return ::read(tty_fd_, buff, size);
}

int TtyReader::fileno() const
{
    return tty_fd_;
}

bool TtyReader::is_open() const
{
    return tty_fd_ >= 0;
}

TtyReader::Poller::Poller(const std::vector<TtyReader *>readers) : readers_(readers)
{
    int n = readers_.size();
    events_.resize(n);
    for (int i = 0;  i < n; i++) {
        events_[i].fd = readers[i]->fileno();
        events_[i].events = POLLIN;
        events_[i].revents = 0;
    }
}

int TtyReader::Poller::poll(int timeout)
{
    return Poll(&events_[0], events_.size(), timeout);
}

const std::vector<struct pollfd> &TtyReader::Poller::getEvents() const
{
    return events_;
}

const std::vector<TtyReader *> &TtyReader::Poller::getReaders() const
{
    return readers_;
}
