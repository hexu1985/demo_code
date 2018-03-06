#pragma once
#include "Poco/Logger.h"

#define logger_handle   (Poco::Logger::get("logger"))

void Logger_initiation();  // initiation
void Setup_logger();       // init only once 

