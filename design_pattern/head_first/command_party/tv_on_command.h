#ifndef __tv_on_command_h
#define __tv_on_command_h

#include <memory>
#include "command.h"
#include "tv.h"

class TVOnCommand: public Command {
private:
    std::shared_ptr<TV> tv;

public:
    TVOnCommand(std::shared_ptr<TV> tv): tv(tv) {
    }

    void execute() override {
        tv->on();
    }

    void undo() override {
        tv->off();
    }
};

#endif
