/*
 * P1 - Light Panel
 * Read the full statement in ..\problems\P1.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Starter functions:
 *   range_mask  - build a mask covering bits a..b inclusive
 *   set_range   - turn every bit in a..b on
 *   clear_range - turn every bit in a..b off
 *   flip_range  - toggle every bit in a..b
 *   get_bit     - read one bit
 *   count_bits  - count the set bits
 *   print_bits  - print all 32 bits, most significant first
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint32_t range_mask(int a, int b) {
    /* TODO: return a mask with bits a..b set. Handle the full 32-bit range. */
    (void)a;
    (void)b;
    return 0;
}

static void set_range(uint32_t *bits, int a, int b) {
    /* TODO: bits |= range_mask(a, b) */
    (void)bits;
    (void)a;
    (void)b;
}

static void clear_range(uint32_t *bits, int a, int b) {
    /* TODO: bits &= ~range_mask(a, b) */
    (void)bits;
    (void)a;
    (void)b;
}

static void flip_range(uint32_t *bits, int a, int b) {
    /* TODO: bits ^= range_mask(a, b) */
    (void)bits;
    (void)a;
    (void)b;
}

static int get_bit(uint32_t bits, int position) {
    /* TODO: return (bits >> position) & 1 */
    (void)bits;
    (void)position;
    return 0;
}

static int count_bits(uint32_t bits) {
    /* TODO: count the set bits (Kernighan's trick is a good choice) */
    (void)bits;
    return 0;
}

static void print_bits(uint32_t bits) {
    /* TODO: print bits 31 down to 0 as '0' or '1', then a newline */
    (void)bits;
}

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) {
        return 0;
    }

    uint32_t bits = 0;
    char command[16];

    for (int i = 0; i < q; i++) {
        if (scanf("%15s", command) != 1) {
            break;
        }

        if (strcmp(command, "SET") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            set_range(&bits, a, b);
        } else if (strcmp(command, "CLEAR") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            clear_range(&bits, a, b);
        } else if (strcmp(command, "FLIP") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            flip_range(&bits, a, b);
        } else if (strcmp(command, "GET") == 0) {
            int position;
            scanf("%d", &position);
            printf("bit %d = %d\n", position, get_bit(bits, position));
        } else if (strcmp(command, "COUNT") == 0) {
            printf("%d\n", count_bits(bits));
        } else if (strcmp(command, "PRINT") == 0) {
            print_bits(bits);
        }
    }

    return 0;
}
