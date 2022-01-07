#include "mynew.hpp"
#include <stdio.h>
#include <stdlib.h>

void *my_operator_new_implement(size_t size) 
{
	printf("my_operator_new_implement malloc\n");
	return malloc(size);
}

void my_operator_delete_implement(void *ptr)
{
	printf("my_operator_delete_implement free\n");
	free(ptr);
}
