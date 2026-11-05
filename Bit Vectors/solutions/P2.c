/*
 * P2 - Sieve of Bits
 * Sieve of Eratosthenes using a bit vector (one bit per number).
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 2) {
        return 0;
    }

    size_t words = (size_t)n / 64 + 1;
    uint64_t *composite = (uint64_t *)calloc(words, sizeof(uint64_t));
    if (composite == NULL) {
        return 1;
    }

    int count = 0;
    int largest = 0;
    long long sum = 0;

    for (int value = 2; value <= n; value++) {
        int is_composite = (int)((composite[value >> 6] >> (value & 63)) & UINT64_C(1));
        if (is_composite) {
            continue;
        }

        count++;
        sum += value;
        largest = value;

        if ((long long)value * value <= n) {
            for (long long multiple = (long long)value * value;
                 multiple <= n;
                 multiple += value) {
                composite[multiple >> 6] |= UINT64_C(1) << (multiple & 63);
            }
        }
    }

    printf("%d\n%lld\n%d\n", count, sum, largest);

    free(composite);
    return 0;
}
