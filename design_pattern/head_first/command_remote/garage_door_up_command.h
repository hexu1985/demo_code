#ifndef __garage_door_up_command_h
#define __garage_door_up_command_h

#include <memory>
#include "command.h"
#include "garage_door.h"

class GarageDoorUpCommand: public Command {
private:
    std::shared_ptr<GarageDoor> garageDoor;

public:
    GarageDoorUpCommand(std::shared_ptr<GarageDoor> garageDoor): garageDoor(garageDoor) {
    }

    void execute() override {
        garageDoor->up();
    }
};

#endif
