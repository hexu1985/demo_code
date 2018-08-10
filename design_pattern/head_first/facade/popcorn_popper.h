#ifndef __popcorn_popper_h
#define __popcorn_popper_h

#include <string>

class PopcornPopper {
private:
    std::string description;

public:
    PopcornPopper(std::string description);

    ~PopcornPopper();

    void on();

    void off();

    void pop();

    std::string toString();

    void clear();
};

#endif
