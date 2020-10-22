#ifndef STORE_FILE_INC
#define STORE_FILE_INC

#include <string>
#include <fstream>

inline
void store_file(const char *file_path, const std::string &content)
{
  std::ofstream f;
  f.exceptions(f.failbit | f.badbit);
  f.open(file_path);
  f << content;
  f.close();
}

#endif
