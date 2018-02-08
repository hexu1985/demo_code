#ifndef __garage_door_down_command_h
#define __garage_door_down_command_h

#include <memory>
#include "command.h"
#include "garage_door.h"

class GarageDoorDownCommand: public Command {
private:
    std::shared_ptr<GarageDoor> garageDoor;

public:
    GarageDoorDownCommand(std::shared_ptr<GarageDoor> garageDoor): garageDoor(garageDoor) {
    }

    void execute() override {
        garageDoor->down();
    }
};

#endif
