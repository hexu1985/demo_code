#include <libnet.h>
#include <stdio.h>

int main()
{
#if (LIBNET_LIL_ENDIAN)
	printf("LIBNET_LIL_ENDIAN\n");
#endif
#if (LIBNET_BIG_ENDIAN)
	printf("LIBNET_BIG_ENDIAN\n");
#endif

	return 0;
}
