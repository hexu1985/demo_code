#include <memory>
#include <iostream>

#include "ceiling_fan.h"
#include "ceiling_fan_off_command.h"
#include "ceiling_fan_on_command.h"
#include "command.h"
#include "garage_door.h"
#include "garage_door_down_command.h"
#include "garage_door_up_command.h"
#include "hottub.h"
#include "hottub_off_command.h"
#include "hottub_on_command.h"
#include "light.h"
#include "light_off_command.h"
#include "light_on_command.h"
#include "livingroom_light_off_command.h"
#include "livingroom_light_on_command.h"
#include "no_command.h"
#include "remote_control.h"
#include "stereo.h"
#include "stereo_off_command.h"
#include "stereo_on_command.h"
#include "stereo_on_with_cd_command.h"

int main(int argc, char *argv[]) 
{
    RemoteControl remoteControl;

    auto livingRoomLight = std::make_shared<Light>("Living Room");
    auto kitchenLight = std::make_shared<Light>("Kitchen");
    auto ceilingFan= std::make_shared<CeilingFan>("Living Room");
    auto garageDoor = std::make_shared<GarageDoor>("");
    auto stereo = std::make_shared<Stereo>("Living Room");

    auto livingRoomLightOn = 
        std::make_shared<LightOnCommand>(livingRoomLight);
    auto livingRoomLightOff = 
        std::make_shared<LightOffCommand>(livingRoomLight);
    auto kitchenLightOn = 
        std::make_shared<LightOnCommand>(kitchenLight);
    auto kitchenLightOff = 
        std::make_shared<LightOffCommand>(kitchenLight);

    auto ceilingFanOn = 
        std::make_shared<CeilingFanOnCommand>(ceilingFan);
    auto ceilingFanOff = 
        std::make_shared<CeilingFanOffCommand>(ceilingFan);

    auto garageDoorUp =
        std::make_shared<GarageDoorUpCommand>(garageDoor);
    auto garageDoorDown =
        std::make_shared<GarageDoorDownCommand>(garageDoor);

    auto stereoOnWithCD =
        std::make_shared<StereoOnWithCDCommand>(stereo);
    auto  stereoOff =
        std::make_shared<StereoOffCommand>(stereo);

    remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remoteControl.setCommand(1, kitchenLightOn, kitchenLightOff);
    remoteControl.setCommand(2, ceilingFanOn, ceilingFanOff);
    remoteControl.setCommand(3, stereoOnWithCD, stereoOff);

    std::cout << remoteControl << std::endl;

    remoteControl.onButtonWasPushed(0);
    remoteControl.offButtonWasPushed(0);
    remoteControl.onButtonWasPushed(1);
    remoteControl.offButtonWasPushed(1);
    remoteControl.onButtonWasPushed(2);
    remoteControl.offButtonWasPushed(2);
    remoteControl.onButtonWasPushed(3);
    remoteControl.offButtonWasPushed(3);

    return 0;
}

