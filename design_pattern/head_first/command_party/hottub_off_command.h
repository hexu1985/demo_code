#ifndef __hottub_off_command_h
#define __hottub_off_command_h

#include <memory>
#include "command.h"
#include "hottub.h"

class HottubOffCommand: public Command {
private:
    std::shared_ptr<Hottub> hottub;

public:
    HottubOffCommand(std::shared_ptr<Hottub> hottub): hottub(hottub) {
    }

    void execute() override {
        hottub->setTemperature(98);
        hottub->off();
    }

    void undo() override {
        hottub->on();
    }
};

#endif
