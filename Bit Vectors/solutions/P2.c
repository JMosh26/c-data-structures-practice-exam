/*
 * P2 - Prime Stamp
 * Answer key: a bit-vector sieve plus prime-gap statistics.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Solution functions:
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
    return (int)((bits[value >> 6] >> (value & 63)) & UINT64_C(1));
}

static void sieve(uint64_t *bits, int n) {
    for (int value = 2; (long long)value * value <= n; value++) {
        if (is_composite(bits, value)) {
            continue;
        }

        for (long long multiple = (long long)value * value;
             multiple <= n;
             multiple += value) {
            bits[multiple >> 6] |= UINT64_C(1) << (multiple & 63);
        }
    }
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
