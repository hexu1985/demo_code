//#include <interface/wemeet_interface.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <coredumper/coredumper.h>

void sig_func(int signo) {
  static int num=0;
  char name[23];
  num++;
  printf("segment fault: caught signal: %d\n",signo);
  sprintf(name,"coredump_%d_%d.core", num, signo);
  if( WriteCoreDump(name) == 0 ) { 
    printf("success: WriteCoreDump to ");
  } else {
    printf("failure: WriteCoreDump to ");
  }

  printf("%s\n", name);   
  exit(-1);//important, comment the line will lead to dead loop signal
}

int main(int argc, char* argv[]) {
  int ret = 0;

  printf("Rotest:wemeetapp:main Test1\n");
  signal(SIGSEGV, &sig_func);
  signal(SIGABRT, &sig_func);
  signal(SIGFPE, &sig_func);

  do
  {
    int a=1;
    int b=0;
    int c=a/b;
    int d=c*2;

    char *q;
    q=nullptr;
    q[1]='s';

  } while (false);

  return ret;
}
