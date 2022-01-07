#define protected public
#include "loki/SmallObj.h"
#include <string.h>
#include <iostream>

using namespace Loki;

int main() 
{
	std::size_t page_size = 4096;
	std::size_t max_object_size = 64;
	std::size_t object_align_size = 4;

	SmallObjAllocator allocator(page_size, max_object_size, object_align_size);
	int buff_sz = 16;
	char *buff = (char *) allocator.Allocate(10, false);
	memset(buff, 0, buff_sz);
	strncpy(buff, "hello world", buff_sz-1);

	std::cout << buff << std::endl;

	allocator.Deallocate(buff);

	return 0;
}
