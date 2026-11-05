/*
 * P3 - Bitset Algebra
 * Read the full statement in ..\problems\P3.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Starter functions:
 *   parse_bits  - convert a binary string to a bit vector
 *   print_bits  - print exactly L bits, most significant first
 *   count_ones  - count the set bits
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint64_t parse_bits(const char *text, int length) {
    /* TODO: start at 0, shift left, and OR in each character's bit */
    (void)text;
    (void)length;
    return 0;
}

static void print_bits(uint64_t value, int length) {
    /* TODO: print bits length - 1 down to 0, then a newline */
    (void)value;
    (void)length;
    putchar('\n');
}

static int count_ones(uint64_t value) {
    /* TODO: return the number of 1 bits */
    (void)value;
    return 0;
}

int main(void) {
    char a[80];
    char b[80];

    if (scanf("%79s %79s", a, b) != 2) {
        return 0;
    }

    int length = (int)strlen(a);
    uint64_t first = parse_bits(a, length);
    uint64_t second = parse_bits(b, length);

    printf("AND: ");
    print_bits(first & second, length);

    printf("OR: ");
    print_bits(first | second, length);

    printf("XOR: ");
    print_bits(first ^ second, length);

    printf("A ones: %d\n", count_ones(first));
    printf("B ones: %d\n", count_ones(second));

    return 0;
}
