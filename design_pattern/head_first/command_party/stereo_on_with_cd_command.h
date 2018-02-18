#ifndef __stereo_on_with_cd_command_h
#define __stereo_on_with_cd_command_h

#include <memory>
#include "command.h"
#include "stereo.h"

class StereoOnWithCDCommand: public Command {
private:
    std::shared_ptr<Stereo> stereo;

public:
    StereoOnWithCDCommand(std::shared_ptr<Stereo> stereo): stereo(stereo) {
    }

    void execute() override {
        stereo->on();
        stereo->setCD();
        stereo->setVolume(11);
    }

    void undo() override {
        stereo->off();
    }
};

#endif

