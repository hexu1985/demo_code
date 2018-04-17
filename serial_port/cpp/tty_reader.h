#ifndef __tty_reader_h
#define __tty_reader_h

#include <vector>

class TtyReader {
private:
    int tty_fd_;
    bool can_read_;
    bool has_error_;

private:
    void reset_flag();
    void set_can_read(bool can_read);
    void set_has_error(bool has_error);
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
    bool canRead() const;
    bool hasError() const;
};

#endif
