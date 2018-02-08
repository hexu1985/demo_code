#ifndef __stereo_on_command_h
#define __stereo_on_command_h

#include <memory>
#include "command.h"
#include "stereo.h"

class StereoOnCommand: public Command {
private:
    std::shared_ptr<Stereo> stereo;

public:
    StereoOnCommand(std::shared_ptr<Stereo> stereo): stereo(stereo) {
    }

    void execute() override {
        stereo->on();
    }
};

#endif

