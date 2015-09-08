/*
 *  fsub.c - marchelzo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdnoreturn.h>

noreturn static void usage(char const *name)
{
    fprintf(stderr, "usage: %s <pattern> <file>\n", name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int c;
    size_t n;
    FILE *f;
    char buffer[512];
    char const *pattern = argv[1];
    char const *p = pattern;

    if (argc != 3)
        usage(argv[0]);

    f = fopen(argv[2], "r");
    if (!f) {
        fprintf(stderr, "Failed to open file: %s\n", argv[2]);
        return 1;
    }

    while (c = getchar(), c != EOF) {
        if (c != *p) {
            fwrite(pattern, 1, p - pattern, stdout);
            p = pattern;
            putchar(c);
            continue;
        }

        if (!*++p) {
            rewind(f);
            p = pattern;

            while (n = fread(buffer, 1, 512, f))
                fwrite(buffer, 1, n, stdout);
        }
    }

    return 0;
}
