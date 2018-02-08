#ifndef __livingroom_light_on_command_h
#define __livingroom_light_on_command_h

#include <memory>
#include "command.h"
#include "light.h"

class LivingroomLightOnCommand: public Command {
private:
    std::shared_ptr<Light> light;

public:
    LivingroomLightOnCommand(std::shared_ptr<Light> light): light(light) {
    }

    void execute() override {
        light->on();
    }

    void undo() override {
        light->off();
    }
};

#endif
