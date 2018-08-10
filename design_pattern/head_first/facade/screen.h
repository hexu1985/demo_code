#ifndef __screen_h
#define __screen_h

#include <string>

class Screen {
private:
    std::string description;

public:
    Screen(std::string description);

    ~Screen();

    void up();

    void down();

    std::string toString();

    void clear();
};

#endif
