#ifndef __ceiling_fan_on_command_h
#define __ceiling_fan_on_command_h

#include <memory>
#include "command.h"
#include "ceiling_fan.h"

class CeilingFanOnCommand: public Command {
private:
    std::shared_ptr<CeilingFan> ceilingFan;

public:
	CeilingFanOnCommand(std::shared_ptr<CeilingFan> ceilingFan): ceilingFan(ceilingFan) {
	}

	void execute() override {
		ceilingFan->high();
	}
};

#endif
