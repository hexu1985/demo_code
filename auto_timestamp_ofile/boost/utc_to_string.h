#ifndef __utc_to_string_h
#define __utc_to_string_h

#include <string>
#include "boost/chrono.hpp"

std::string utc_to_string(const boost::chrono::system_clock::time_point &tp);

#endif

