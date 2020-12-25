#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  unsigned int ngx_ncpu = 0;

  ngx_ncpu = sysconf(_SC_NPROCESSORS_ONLN);
  printf("ncpu = %d\n", ngx_ncpu);

  return 0;
}
