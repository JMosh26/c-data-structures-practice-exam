/*
 * P2 - Sieve of Bits
 * Answer key: Sieve of Eratosthenes using a bit vector.
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
