#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  unsigned int n = 0;

  n = sysconf(_SC_NPROCESSORS_ONLN);
  printf("processor count = %d\n", n);

  return 0;
}
