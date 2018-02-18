#include <memory>
#include <iostream>

#include "ceiling_fan.h"
#include "ceiling_fan_off_command.h"
#include "ceiling_fan_high_comannd.h"
#include "ceiling_fan_medium_command.h"
#include "command.h"
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
#include "tv.h"
#include "tv_off_command.h"
#include "tv_on_command.h"
#include "macro_command.h"

int main(int argc, char *argv[]) 
{
    RemoteControl remoteControl;

    auto light = std::make_shared<Light>("Living Room");
    auto tv = std::make_shared<TV>("Living Room");
    auto stereo = std::make_shared<Stereo>("Living Room");
    auto hottub = std::make_shared<Hottub>();

    auto lightOn = std::make_shared<LightOnCommand>(light);
    auto stereoOn = std::make_shared<StereoOnCommand>(stereo);
    auto tvOn = std::make_shared<TVOnCommand>(tv);
    auto hottubOn = std::make_shared<HottubOnCommand>(hottub);
    auto lightOff = std::make_shared<LightOffCommand>(light);
    auto stereoOff = std::make_shared<StereoOffCommand>(stereo);
    auto tvOff = std::make_shared<TVOffCommand>(tv);
    auto hottubOff = std::make_shared<HottubOffCommand>(hottub);

    std::vector<std::shared_ptr<Command>> partyOn = { lightOn, stereoOn, tvOn, hottubOn};
    std::vector<std::shared_ptr<Command>> partyOff = { lightOff, stereoOff, tvOff, hottubOff};

    auto partyOnMacro = std::make_shared<MacroCommand>(partyOn);
    auto partyOffMacro = std::make_shared<MacroCommand>(partyOff);

    remoteControl.setCommand(0, partyOnMacro, partyOffMacro);

    std::cout << remoteControl << '\n';
    std::cout << "--- Pushing Macro On---" << '\n';
    remoteControl.onButtonWasPushed(0);
    std::cout << "--- Pushing Macro Off---" << '\n';
    remoteControl.offButtonWasPushed(0);
    return 0;
}

