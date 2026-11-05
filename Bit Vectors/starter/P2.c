/*
 * P2 - Prime Stamp
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
    /* TODO: allocate (n / 64 + 1) uint64_t words with calloc */
    (void)n;
    return NULL;
}

static int is_composite(const uint64_t *bits, int value) {
    /* TODO: read bit `value` from the bitset */
    (void)bits;
    (void)value;
    return 0;
}

static void sieve(uint64_t *bits, int n) {
    /* TODO: mark multiples of every prime starting at prime * prime */
    (void)bits;
    (void)n;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 2) {
        printf("primes: 0\n");
        printf("sum: 0\n");
        printf("largest: 0\n");
        printf("gap: 0\n");
        printf("pair: none\n");
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
    int previous = -1;
    int best_gap = 0;
    int gap_left = 0;
    int gap_right = 0;

    for (int value = 2; value <= n; value++) {
        if (is_composite(composite, value)) {
            continue;
        }

        count++;
        sum += value;
        largest = value;

        if (previous >= 0) {
            int gap = value - previous;
            if (gap > best_gap) {
                best_gap = gap;
                gap_left = previous;
                gap_right = value;
            }
        }

        previous = value;
    }

    printf("primes: %d\n", count);
    printf("sum: %lld\n", sum);
    printf("largest: %d\n", largest);
    printf("gap: %d\n", best_gap);

    if (count >= 2) {
        printf("pair: %d %d\n", gap_left, gap_right);
    } else {
        printf("pair: none\n");
    }

    free(composite);
    return 0;
}
