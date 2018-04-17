#ifndef __tty_reader_h
#define __tty_reader_h

#include <vector>
#include <poll.h>

class TtyReader {
private:
    int tty_fd_;

private:
    void check_open() const;

public:
    TtyReader();
    ~TtyReader();

    void open(const char *dev);
    void open(const char *dev, int oflag);
    void close();

    void setSpeed(int speed);
    void setParity(int databits, int stopbits, int parity);
    void setIcanon(int echo, int icanon);
    void setTimeout(int min, int sec, int millisec);

    int read(char *buffer, int size);

    int fileno() const;
    bool is_open() const;

public:
    class Poller {
    private:
        std::vector<struct pollfd> events_;
        std::vector<TtyReader *> readers_;

    public:
        Poller();
        void watch(const std::vector<TtyReader *>readers);
        void unwatch(TtyReader *readers);
        int poll(int timeout);
        const std::vector<struct pollfd> &getEvents() const;
        const std::vector<TtyReader *> &getReaders() const;
    };
};

#endif
