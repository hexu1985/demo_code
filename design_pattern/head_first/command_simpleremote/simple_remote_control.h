#ifndef __simple_remote_control_h
#define __simple_remote_control_h

#include <memory>
#include "command.h"

class SimpleRemoteControl {
private:
    std::unique_ptr<Command> slot;

public:
    SimpleRemoteControl() {
    }

    void setCommand(std::unique_ptr<Command> command) {
        slot = std::move(command);
    }

    void buttonWasPressed() {
        slot->execute();
    }
};

#endif
