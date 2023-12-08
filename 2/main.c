#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRLEN(x) (sizeof(x) / sizeof(*x))
#define PART      2
#define INPUT     "./input.txt"

#if PART != 1 && PART != 2
#error "Please set PART to either 1 or 2"
#endif

int
analyze(char *buf, int max_red, int max_green, int max_blue)
{
    if (buf == NULL)
        return 0;

    int id = 0, red = 0, green = 0, blue = 0, offset = 0;
    sscanf(buf, "Game %d:%n", &id, &offset);

    char *tok = buf + (sizeof(*buf) * offset);
    while ((tok = strtok(tok, ";")) != NULL) {
        static char name[6]; // "green" is the longest color
        static int amount, offset;

        while ((sscanf(tok, " %d %[^,\n]%n", &amount, name, &offset)) != EOF) {
            tok += (sizeof(*tok) * offset);
            if (tok[0] == ',' || tok[0] == '\n')
                tok += sizeof(*tok);

            char c = name[0];
            int *color = c == 'r' ? &red : c == 'g' ? &green : &blue;
#if PART == 1
            if (*color < amount)
                *color = amount;
#elif PART == 2
            if (*color == 0 || *color < amount)
                *color = amount;
#endif
        }

        tok = NULL;
    }

#if PART == 1
    return (max_red < red || max_green < green || max_blue < blue) ? 0 : id;
#elif PART == 2
    return red * green * blue;
#endif
}

int
main(void)
{
    FILE *f = fopen(INPUT, "r");
    if (f == NULL) {
        exit(EXIT_FAILURE);
    }

    long long total = 0;
    char buff[1 << 10] = {0};
    while (fgets(buff, ARRLEN(buff), f) != NULL) {
        total += analyze(buff, 12, 13, 14);
    }
    printf("%lld\n", total);

    fclose(f);
    return 0;
}
