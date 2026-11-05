/*
 * P3 - Set Duel
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
 *   is_subset   - true when every bit of A is also in B
 *   is_disjoint - true when A and B share no bits
 *   same_set    - true when A and B are identical
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint64_t parse_bits(const char *text, int length) {
    /* TODO: shift left and OR each '1' bit */
    (void)text;
    (void)length;
    return 0;
}

static void print_bits(uint64_t value, int length) {
    /* TODO: print length bits, most significant first, then a newline */
    (void)value;
    (void)length;
}

static int count_ones(uint64_t value) {
    /* TODO: count the set bits */
    (void)value;
    return 0;
}

static int is_subset(uint64_t a, uint64_t b) {
    /* TODO: return (a & ~b) == 0 */
    (void)a;
    (void)b;
    return 0;
}

static int is_disjoint(uint64_t a, uint64_t b) {
    /* TODO: return (a & b) == 0 */
    (void)a;
    (void)b;
    return 0;
}

static int same_set(uint64_t a, uint64_t b) {
    /* TODO: return a == b */
    (void)a;
    (void)b;
    return 0;
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
