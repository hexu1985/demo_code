#ifndef __basename_h
#define __basename_h

#include <string>
#include "boost/filesystem.hpp"

inline
std::string basename(const std::string &path_str)
{
    boost::filesystem::path path(path_str);
    return path.filename().string();
}

#endif
