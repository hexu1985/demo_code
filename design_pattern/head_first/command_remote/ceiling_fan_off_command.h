#ifndef __ceiling_fan_off_command_h
#define __ceiling_fan_off_command_h

#include <memory>
#include "command.h"
#include "ceiling_fan.h"

class CeilingFanOffCommand: public Command {
private:
    std::shared_ptr<CeilingFan> ceilingFan;

public:
	CeilingFanOffCommand(std::shared_ptr<CeilingFan> ceilingFan): ceilingFan(ceilingFan) {
	}

	void execute() override {
		ceilingFan->off();
	}
};

#endif
