#ifndef __stereo_off_command_h
#define __stereo_off_command_h

#include <memory>
#include "command.h"
#include "stereo.h"

class StereoOffCommand: public Command {
private:
    std::shared_ptr<Stereo> stereo;

public:
    StereoOffCommand(std::shared_ptr<Stereo> stereo): stereo(stereo) {
    }

    void execute() override {
        stereo->off();
    }

    void undo() override {
        stereo->on();
    }
};

#endif

