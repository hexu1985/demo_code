#ifndef __light_off_command_h
#define __light_off_command_h

#include <memory>
#include "command.h"
#include "light.h"

class LightOffCommand: public Command {
private:
    std::shared_ptr<Light> light;

public:
    LightOffCommand(std::shared_ptr<Light> light): light(light) {
    }

    void execute() override {
        light->off();
    }
};

#endif
