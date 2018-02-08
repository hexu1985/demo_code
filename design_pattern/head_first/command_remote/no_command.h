#ifndef __no_command_h
#define __no_command_h

#include "command.h"

class NoCommand: public Command {
public:
    void execute() override { }
};

#endif
