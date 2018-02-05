#ifndef __ZHELPERS_S_RAND_H_INCLUDED__
#define __ZHELPERS_S_RAND_H_INCLUDED__

#include <stdlib.h>

//  On some version of Windows, POSIX subsystem is not installed by default.
//  So define srandom and random ourself.
#ifndef srandom
#define srandom srand
#endif

#ifndef random
#define random rand
#endif

//  Provide random number from 0..(num-1)
#define randof(num)  (int) ((float) (num) * random () / (RAND_MAX + 1.0))

#endif
