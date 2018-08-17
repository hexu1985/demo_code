#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" //support for stdout logging

int main(int, char* [])
{
    //Multithreaded console logger(with color support)
    auto console = spdlog::stdout_color_mt("console");
    console->set_level(spdlog::level::trace);
    console->info("Welcome to spdlog!") ;
    console->info("An info message example {}..", 1);

    SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
    SPDLOG_DEBUG(console, "Enabled only #ifdef SPDLOG_DEBUG_ON.. {} ,{}", 1, 3.23);

    return 0;
}
