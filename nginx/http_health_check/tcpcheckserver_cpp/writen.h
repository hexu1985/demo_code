#ifndef __unp_writen_h
#define __unp_writen_h

#include <unistd.h>
#include "error.h"

#ifdef  __cplusplus
extern "C" {
#endif

ssize_t     writen(int, const void *, size_t);
void        Writen(int, void *, size_t);

#ifdef  __cplusplus
}   // extern "C"
#endif

#endif

