#include <stdio.h>
#include <netdb.h>

struct Herror {
    int error;
    const char* name;
};

int main()
{
    struct Herror herror_list[] = {
        {HOST_NOT_FOUND, "HOST_NOT_FOUND"},
        {NO_DATA, "NO_DATA"},
        {NO_RECOVERY, "NO_RECOVERY"},
        {TRY_AGAIN, "TRY_AGAIN"},
    };

    for (int i = 0; i < sizeof(herror_list)/sizeof(struct Herror); i++) {
        printf("%s: %s\n", herror_list[i].name, hstrerror(herror_list[i].error));
    }

    return 0;
}
