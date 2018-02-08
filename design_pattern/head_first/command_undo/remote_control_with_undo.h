#ifndef __remote_control_h
#define __remote_control_h

#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include "command.h"
#include "no_command.h"

class RemoteControlWithUndo {
private:
    std::vector<CommandPtr> onCommands;
    std::vector<CommandPtr> offCommands;
    std::shared_ptr<Command> undoCommand;
 
public:
    RemoteControlWithUndo() {
        onCommands.resize(7);
        offCommands.resize(7);
 
        auto noCommand = std::make_shared<NoCommand>();
        for (int i = 0; i < 7; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
        undoCommand = noCommand;
    }
  
    void setCommand(int slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand) {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
 
    void onButtonWasPushed(int slot) {
        onCommands[slot]->execute();
        undoCommand = onCommands[slot];
    }
 
    void offButtonWasPushed(int slot) {
        offCommands[slot]->execute();
        undoCommand = onCommands[slot];
    }

    void undoButtonWasPushed() {
        undoCommand->undo(); 
    }
  
    friend std::ostream &operator <<(std::ostream &out, const RemoteControlWithUndo &remote_control) {
        out << "\n------ Remote Control -------\n";
        for (int i = 0; i < remote_control.onCommands.size(); i++) {
            out << "[slot " << i << "] " << typeid(*remote_control.onCommands[i]).name()
                << "    " << typeid(*remote_control.offCommands[i]).name() << "\n";
        }
        out << "[undo] " << typeid(*remote_control.undoCommand).name() << "\n";
        return out;
    }
};

#endif
