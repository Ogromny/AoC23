#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT     "./input.txt"
#define ARRLEN(x) (sizeof(x) / sizeof(*x))

static char *numbers[9] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
};

static int
match_literal_digit(char const *const buf, size_t len)
{
    if (buf == NULL || buf[0] == '\0') {
        return 0;
    }

    int candidates[2] = {0}; // 1..=9 only two numbers start with same letter
    size_t candidates_pos = 0;

    char c = buf[0];
    for (size_t i = 0, j = ARRLEN(numbers); i < j; ++i) {
        if (numbers[i][0] == c) {
            candidates[candidates_pos++] = i;
        }
    }

    for (size_t i = 0; i < candidates_pos; ++i) {
        char *s = numbers[candidates[i]];
        if (strncmp(buf, s, strlen(s)) == 0) {
            printf("matched %s -> %d\n", s, candidates[i] + 1);
            return candidates[i] + 1; // 0 based
        }
    }

    return 0;
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
        int first = 0, second = 0, m = 0;

        for (size_t i = 0, j = strlen(buff); i < j; ++i) {
            if (isdigit(buff[i])) {
                m = buff[i] - '0';
            } else if ((m = match_literal_digit(buff + sizeof(*buff) * i, j - i)) == 0) {
                continue;
            }
            *(first == 0 ? &first : &second) = m;
        }
        total += first * 10 + (second == 0 ? first : second);
    }
    printf("%lld\n", total);

    fclose(f);
    return 0;
}
