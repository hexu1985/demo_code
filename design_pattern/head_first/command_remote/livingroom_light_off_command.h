#ifndef __livingroom_light_off_command_h
#define __livingroom_light_off_command_h

#include <memory>
#include "command.h"
#include "light.h"

class LivingroomLightOffCommand: public Command {
private:
    std::shared_ptr<Light> light;

public:
    LivingroomLightOffCommand(std::shared_ptr<Light> light): light(light) {
    }

    void execute() override {
        light->off();
    }
};

#endif
