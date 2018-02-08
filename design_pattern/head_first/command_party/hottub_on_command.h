#ifndef __hottub_on_command_h
#define __hottub_on_command_h

#include <memory>
#include "command.h"
#include "hottub.h"

class HottubOnCommand: public Command {
private:
    std::shared_ptr<Hottub> hottub;

public:
    HottubOnCommand(std::shared_ptr<Hottub> hottub): hottub(hottub) {
    }

    void execute() override {
        hottub->on();
        hottub->setTemperature(104);
        hottub->circulate();
    }

    void undo() override {
        hottub->off();
    }
};

#endif
