/*
 * P1 - Light Panel
 * Answer key: a 32-bit panel with range SET / CLEAR / FLIP operations.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
 *   range_mask - build a mask covering bits a..b inclusive
 *   set_range  - turn every bit in a..b on
 *   clear_range- turn every bit in a..b off
 *   flip_range - toggle every bit in a..b
 *   get_bit    - read one bit
 *   count_bits - count the set bits
 *   print_bits - print all 32 bits, most significant first
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint32_t range_mask(int a, int b) {
    int width = b - a + 1;
    if (width >= 32) {
        return UINT32_MAX;
    }
    return ((UINT32_C(1) << width) - 1) << a;
}

static void set_range(uint32_t *bits, int a, int b) {
    *bits |= range_mask(a, b);
}

static void clear_range(uint32_t *bits, int a, int b) {
    *bits &= ~range_mask(a, b);
}

static void flip_range(uint32_t *bits, int a, int b) {
    *bits ^= range_mask(a, b);
}

static int get_bit(uint32_t bits, int position) {
    return (int)((bits >> position) & UINT32_C(1));
}

static int count_bits(uint32_t bits) {
    int count = 0;

    while (bits != 0) {
        bits &= bits - UINT32_C(1);
        count++;
    }

    return count;
}

static void print_bits(uint32_t bits) {
    for (int position = 31; position >= 0; position--) {
        putchar(((bits >> position) & UINT32_C(1)) ? '1' : '0');
    }
    putchar('\n');
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
