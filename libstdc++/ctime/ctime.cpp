/* ctime example */
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, time, ctime */

int main ()
{
  time_t rawtime;

  time (&rawtime);
  printf ("The current local time is: %s", ctime (&rawtime));

  return 0;
}


/*
Output:

The current local time is: Wed Feb 13 16:06:10 2013
*/
