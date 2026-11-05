/*
 * P3 - Bitset Algebra
 * Answer key: load two binary strings and apply bitwise set operations.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Solution functions:
 *   parse_bits  - convert a binary string to a bit vector
 *   print_bits  - print exactly L bits, most significant first
 *   count_ones  - count the set bits
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint64_t parse_bits(const char *text, int length) {
    uint64_t value = 0;

    for (int i = 0; i < length; i++) {
        value = (value << 1) | (text[i] == '1' ? UINT64_C(1) : UINT64_C(0));
    }

    return value;
}

static void print_bits(uint64_t value, int length) {
    for (int position = length - 1; position >= 0; position--) {
        putchar(((value >> position) & UINT64_C(1)) ? '1' : '0');
    }
    putchar('\n');
}

static int count_ones(uint64_t value) {
    int count = 0;

    while (value != 0) {
        value &= value - UINT64_C(1);
        count++;
    }

    return count;
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
