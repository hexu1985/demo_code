#ifndef __mynew_hpp
#define __mynew_hpp

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *my_operator_new_implement(size_t size);
void my_operator_delete_implement(void *ptr);

#ifdef __cplusplus
}	// extern "C"
#endif

#endif
