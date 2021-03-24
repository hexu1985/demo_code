#include <stdio.h>
#include <string>
#include <iostream>
#include <regex>


int main(int argc, char *argv[])
{
  std::string command = "lscpu";
  FILE *f = popen(command.c_str(), "r");
  if (f == NULL) {
    std::cout << "popen(" << command << ")" << std::endl;
    return 1;
  }

  std::regex cpu_core_rgx("^CPU\\(s\\).*[ \\t]+([0-9]+).*$");
  std::regex cpu_mhz_rgx("^CPU.*MHz.*[ \\t]+([0-9]+).*$");
  const int buf_size = 1024;
  char buf[buf_size] = {0};
  std::string line;
  while (fgets(buf, buf_size, f) != NULL) {
    line = buf;
    if (line.back() == '\n')
      line.pop_back();
    std::smatch sm;
    std::cout  << "line: [" << line << "]" << std::endl;
    if (std::regex_match (line, sm, cpu_mhz_rgx)) {
      std::cout << sm.size() << std::endl;
      for (int i = 0; i < sm.size(); i++) {
        std::cout << i << ". " << sm[i] << std::endl;
      }
    }
    if (std::regex_match (line, sm, cpu_core_rgx)) {
      std::cout << sm.size() << std::endl;
      for (int i = 0; i < sm.size(); i++) {
        std::cout << i << ". " << sm[i] << std::endl;
      }
    }
  }
  return 0;
}
