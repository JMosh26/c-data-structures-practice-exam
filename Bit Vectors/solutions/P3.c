/*
 * P3 - Set Duel
 * Answer key: load two binary strings and compare them as bit sets.
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
 *   is_subset   - true when every bit of A is also in B
 *   is_disjoint - true when A and B share no bits
 *   same_set    - true when A and B are identical
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

static int is_subset(uint64_t a, uint64_t b) {
    return (a & ~b) == 0;
}

static int is_disjoint(uint64_t a, uint64_t b) {
    return (a & b) == 0;
}

static int same_set(uint64_t a, uint64_t b) {
    return a == b;
}

int main(void) {
    int length;
    char a[80];
    char b[80];

    if (scanf("%d %79s %79s", &length, a, b) != 3) {
        return 0;
    }

    if (length < 1 || length > 64) {
        return 0;
    }

    uint64_t first = parse_bits(a, length);
    uint64_t second = parse_bits(b, length);

    printf("AND: ");
    print_bits(first & second, length);

    printf("OR: ");
    print_bits(first | second, length);

    printf("XOR: ");
    print_bits(first ^ second, length);

    printf("NOT: ");
    print_bits(~first, length);

    printf("A: %d\n", count_ones(first));
    printf("B: %d\n", count_ones(second));
    printf("INTERSECTION: %d\n", count_ones(first & second));
    printf("UNION: %d\n", count_ones(first | second));
    printf("SUBSET: %s\n", is_subset(first, second) ? "yes" : "no");
    printf("DISJOINT: %s\n", is_disjoint(first, second) ? "yes" : "no");
    printf("SAME: %s\n", same_set(first, second) ? "yes" : "no");

    return 0;
}
