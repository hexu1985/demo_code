#ifndef __tv_off_command_h
#define __tv_off_command_h

#include <memory>
#include "command.h"
#include "tv.h"

class TVOffCommand: public Command {
private:
    std::shared_ptr<TV> tv;

public:
    TVOffCommand(std::shared_ptr<TV> tv): tv(tv) {
    }

    void execute() override {
        tv->off();
    }

    void undo() override {
        tv->on();
    }
};

#endif
