#ifndef __macro_command_h
#define __macro_command_h

#include <vector>
#include <memory>
#include "command.h"

class MacroCommand: public Command {
private:
    std::vector<CommandPtr> commands;

public:
    MacroCommand(const std::vector<CommandPtr> &commands): commands(commands) {
    }
 
    void execute() {
        for (int i = 0; i < commands.size(); i++) {
            commands[i]->execute();
        }
    }
 
    void undo() {
        for (int i = 0; i < commands.size(); i++) {
            commands[i]->undo();
        }
    }
};

#endif
