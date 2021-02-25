#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main()
{
    const char *dir = "/dev/disk/by-uuid/";

    DIR *dp;
    struct dirent *entry;
    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return 0;
    }
    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;
        printf("entry name: %s\n", entry->d_name);
    }
    closedir(dp);
    return 0;
}
