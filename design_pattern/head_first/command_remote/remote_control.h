#ifndef __remote_control_h
#define __remote_control_h

#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include "command.h"

class RemoteControl {
public:
    typedef std::unique_ptr<Command> CommandPtr;

private:
    std::vector<CommandPtr> onCommands;
    std::vector<CommandPtr> offCommands;
 
public:
    RemoteControl() {
        onCommands.resize(7);
        offCommands.resize(7);
 
        for (int i = 0; i < 7; i++) {
            onCommands[i] = std::make_unique<NoCommand>();
            offCommands[i] = std::make_unique<NoCommand>();
        }
    }
  
    void setCommand(int slot, std::unique_ptr<Command> onCommand, std::unique_ptr<Command> offCommand) {
        onCommands[slot] = std::move(onCommand);
        offCommands[slot] = std::move(offCommand);
    }
 
    void onButtonWasPushed(int slot) {
        onCommands[slot]->execute();
    }
 
    void offButtonWasPushed(int slot) {
        offCommands[slot]->execute();
    }
  
    friend std::ostream &operator <<(std::ostream &out, const RemoteControl &remote_control) {
        out << "\n------ Remote Control -------\n";
        for (int i = 0; i < remote_control.onCommands.size(); i++) {
            out << "[slot " << i << "] " << typeid(*remote_control.onCommands[i]).name()
                << "    " << typeid(*remote_control.offCommands[i]).name() << "\n";
        }
        return out;
    }
};

#endif
