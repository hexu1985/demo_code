#include <memory>
#include <iostream>
#include "ceiling_fan.h"
#include "ceiling_fan_high_comannd.h"
#include "ceiling_fan_low_command.h"
#include "ceiling_fan_medium_command.h"
#include "ceiling_fan_off_command.h"
#include "command.h"
#include "light.h"
#include "light_off_command.h"
#include "light_on_command.h"
#include "livingroom_light_off_command.h"
#include "livingroom_light_on_command.h"
#include "remote_control_with_undo.h"

int main(int argc, char *argv[]) {
	RemoteControlWithUndo remoteControl;

	auto livingRoomLight = std::make_shared<Light>("Living Room");

	auto livingRoomLightOn = 
			std::make_shared<LightOnCommand>(livingRoomLight);
	auto livingRoomLightOff = 
			std::make_shared<LightOffCommand>(livingRoomLight);

	remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff);

	remoteControl.onButtonWasPushed(0);
	remoteControl.offButtonWasPushed(0);
    std::cout << remoteControl << std::endl;
	remoteControl.undoButtonWasPushed();
	remoteControl.offButtonWasPushed(0);
	remoteControl.onButtonWasPushed(0);
    std::cout << remoteControl << std::endl;
	remoteControl.undoButtonWasPushed();

	auto ceilingFan = std::make_shared<CeilingFan>("Living Room");

	auto ceilingFanMedium = 
			std::make_shared<CeilingFanMediumCommand>(ceilingFan);
	auto ceilingFanHigh = 
			std::make_shared<CeilingFanHighCommand>(ceilingFan);
	auto ceilingFanOff = 
			std::make_shared<CeilingFanOffCommand>(ceilingFan);

	remoteControl.setCommand(0, ceilingFanMedium, ceilingFanOff);
	remoteControl.setCommand(1, ceilingFanHigh, ceilingFanOff);

	remoteControl.onButtonWasPushed(0);
	remoteControl.offButtonWasPushed(0);
    std::cout << remoteControl << std::endl;
	remoteControl.undoButtonWasPushed();

	remoteControl.onButtonWasPushed(1);
    std::cout << remoteControl << std::endl;
	remoteControl.undoButtonWasPushed();

    return 0;
}

