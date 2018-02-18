#ifndef __command_h
#define __command_h

class Command {
public:
    virtual ~Command() {}

    virtual void execute() = 0;
    virtual void undo() = 0;
};

typedef std::shared_ptr<Command> CommandPtr;

#endif
