/*
 * P2 - Sieve of Bits
 * Read the full statement in ..\problems\P2.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Starter functions:
 *   create_bitset - allocate enough 64-bit words for N + 1 bits
 *   is_composite  - test one bit
 *   sieve         - mark every composite number
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t *create_bitset(int n) {
    size_t words = (size_t)n / 64 + 1;
    return (uint64_t *)calloc(words, sizeof(uint64_t));
}

static int is_composite(const uint64_t *bits, int value) {
    /* TODO: return (bits[value >> 6] >> (value & 63)) & 1ULL */
    (void)bits;
    (void)value;
    return 0;
}

static void sieve(uint64_t *bits, int n) {
    /* TODO: for every prime p, set the bits of p*p, p*p + p, ... up to n.
       You may add your own mark_composite() helper. */
    (void)bits;
    (void)n;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 2) {
        return 0;
    }

    uint64_t *composite = create_bitset(n);
    if (composite == NULL) {
        return 1;
    }

    sieve(composite, n);

    int count = 0;
    int largest = 0;
    long long sum = 0;

    for (int value = 2; value <= n; value++) {
        if (!is_composite(composite, value)) {
            count++;
            sum += value;
            largest = value;
        }
    }

    printf("%d\n%lld\n%d\n", count, sum, largest);

    free(composite);
    return 0;
}
