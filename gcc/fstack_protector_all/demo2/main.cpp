#include <alloca.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char str[2];
}overflow_t;

int main(void) 
{
	char *str = "welcom to China";

    overflow_t v;  

    printf("sizoef(v) = %d\n", sizeof(v));

    memcpy(&v, str, strlen(str));

    printf("v.str = %s\n", v.str);
}
