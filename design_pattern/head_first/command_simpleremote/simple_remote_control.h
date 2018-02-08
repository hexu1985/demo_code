#ifndef __simple_remote_control_h
#define __simple_remote_control_h

#include <memory>
#include "command.h"

class SimpleRemoteControl {
private:
    std::shared_ptr<Command> slot;

public:
    SimpleRemoteControl() {
    }

    void setCommand(std::shared_ptr<Command> command) {
        slot = command;
    }

    void buttonWasPressed() {
        slot->execute();
    }
};

#endif
