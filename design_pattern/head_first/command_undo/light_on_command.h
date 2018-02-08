#ifndef __light_on_command_h
#define __light_on_command_h

#include <memory>
#include "command.h"
#include "light.h"

class LightOnCommand: public Command {
private:
    std::shared_ptr<Light> light;

public:
    LightOnCommand(std::shared_ptr<Light> light): light(light) {
    }

    void execute() override {
        light->on();
    }

    void undo() override {
        light->off();
    }
};

#endif
