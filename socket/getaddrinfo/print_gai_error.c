#include <stdio.h>
#include <netdb.h>

struct Gai_error {
    int error;
    const char* name;
};

int main()
{
    struct Gai_error gai_error_list[] = {
        {EAI_AGAIN, "EAI_AGAIN"},
        {EAI_BADFLAGS, "EAI_BADFLAGS"},
        {EAI_FAIL, "EAI_FAIL"},
        {EAI_FAMILY, "EAI_FAMILY"},
        {EAI_MEMORY, "EAI_MEMORY"},
        {EAI_NONAME, "EAI_NONAME"},
        {EAI_SERVICE, "EAI_SERVICE"},
        {EAI_SOCKTYPE, "EAI_SOCKTYPE"},
        {EAI_SYSTEM, "EAI_SYSTEM"}
    };

    for (int i = 0; i < sizeof(gai_error_list)/sizeof(struct Gai_error); i++) {
        printf("%s(%d): %s\n", gai_error_list[i].name, gai_error_list[i].error, gai_strerror(gai_error_list[i].error));
    }

    return 0;
}

