#ifndef __garage_door_open_command_h
#define __garage_door_open_command_h

#include <memory>
#include "command.h"
#include "garage_door.h"

class GarageDoorOpenCommand: public Command {
private:
    std::shared_ptr<GarageDoor> garageDoor;

public:
    GarageDoorOpenCommand(std::shared_ptr<GarageDoor> garageDoor): garageDoor(garageDoor) {
    }

    void execute() override {
        garageDoor->up();
    }
};

#endif
