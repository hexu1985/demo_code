#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: file2word file\n");
        exit(1);
    }

    char *filename = argv[1];

    FILE *file;
    char buf[256];
    if ((file = fopen(filename, "r")) == NULL) {
        perror("open file fail");
        exit(1);
    }

    char separators[ ] = " \t\n.:?!\";/[]{}()1234567890\\=,+-'%*#<>";
    char *start = NULL, *end = NULL;
    char word[128];
    while (fgets(buf, sizeof(buf), file) != NULL) {
        start = buf;
        while ( ( end = strpbrk( start, separators ) ) != NULL ) {
            if ( end != start ) // If the separator wasn't the first character,
                { // then save a word in an array.
                    strncpy( word, start, end - start );
                    word[end - start] = '\0'; // And terminate it.
                    printf("%s\n", word);
                }
            start = end + 1; // Next strpbrk call starts with
        } // the character after this separator.
    }

    fclose(file);

    return 0;
}
