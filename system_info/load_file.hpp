#ifndef LOAD_FILE_INC
#define LOAD_FILE_INC

#include <string>
#include <fstream>

inline
std::string load_file(const char *file_path)
{
    std::ifstream f;
    f.exceptions(f.failbit | f.badbit);
    f.open(file_path);
    return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
}

inline
std::string load_file_first_line(const char *file_path)
{
    std::ifstream f;
    f.exceptions(f.failbit | f.badbit);
    f.open(file_path);
    std::string line;
    std::getline(f, line);
    return line;
}

#endif
