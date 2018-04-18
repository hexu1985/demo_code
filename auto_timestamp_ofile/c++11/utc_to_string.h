#ifndef __utc_to_string_h
#define __utc_to_string_h

#include <string>
#include <chrono>

std::string utc_to_string(const std::chrono::system_clock::time_point &tp);

#endif

