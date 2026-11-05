/*
 * P3 - Bitset Algebra
 * Load two binary strings into bit vectors and apply set operations.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void print_bits(uint64_t value, int length) {
    for (int position = length - 1; position >= 0; position--) {
        putchar(((value >> position) & UINT64_C(1)) ? '1' : '0');
    }
    putchar('\n');
}

int main(void) {
    char a[80];
    char b[80];

    if (scanf("%79s %79s", a, b) != 2) {
        return 0;
    }

    int length = (int)strlen(a);
    if (length != (int)strlen(b) || length < 1 || length > 64) {
        return 0;
    }

    uint64_t first = 0;
    uint64_t second = 0;

    for (int i = 0; i < length; i++) {
        first = (first << 1) | (a[i] == '1' ? UINT64_C(1) : UINT64_C(0));
        second = (second << 1) | (b[i] == '1' ? UINT64_C(1) : UINT64_C(0));
    }

    printf("AND: ");
    print_bits(first & second, length);
    printf("OR: ");
    print_bits(first | second, length);
    printf("XOR: ");
    print_bits(first ^ second, length);
    printf("A ones: %d\n", __builtin_popcountll(first));
    printf("B ones: %d\n", __builtin_popcountll(second));

    return 0;
}
