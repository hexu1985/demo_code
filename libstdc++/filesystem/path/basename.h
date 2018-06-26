#ifndef __basename_h
#define __basename_h

#include <string>
#include <filesystem>

inline
std::string basename(const std::string &path_str)
{
    std::filesystem::path path(path_str);
    return path.filename().string();
}

#endif
