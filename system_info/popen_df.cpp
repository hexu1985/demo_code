#include <stdio.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  const char *path = "/";
  if (argc > 1) {
    path = argv[1];
  }

  std::string command = "df";
  command += " ";
  command += path;
  FILE *f = popen(command.c_str(), "r");
  if (f == NULL) {
    std::cout << "popen(" << command << ")" << std::endl;
    return 1;
  }

  const int buf_size = 1024;
  char buf[buf_size] = {0};
  while (fgets(buf, buf_size, f) != NULL) {
    printf("%s", buf);
  }
  return 0;
}
