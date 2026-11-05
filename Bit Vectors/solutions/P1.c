/*
 * P1 - Bit Vector Playground
 * Answer key: a 64-bit vector with SET / CLEAR / FLIP / GET / COUNT / PRINT.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
 *   set_bit    - turn one bit on
 *   clear_bit  - turn one bit off
 *   flip_bit   - toggle one bit
 *   get_bit    - read one bit
 *   count_bits - count the set bits
 *   print_bits - print all 64 bits, most significant first
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void set_bit(uint64_t *bits, int position) {
    *bits |= UINT64_C(1) << position;
}

static void clear_bit(uint64_t *bits, int position) {
    *bits &= ~(UINT64_C(1) << position);
}

static void flip_bit(uint64_t *bits, int position) {
    *bits ^= UINT64_C(1) << position;
}

static int get_bit(uint64_t bits, int position) {
    return (int)((bits >> position) & UINT64_C(1));
}

static int count_bits(uint64_t bits) {
    int count = 0;

    while (bits != 0) {
        bits &= bits - UINT64_C(1);
        count++;
    }

    return count;
}

static void print_bits(uint64_t bits) {
    for (int position = 63; position >= 0; position--) {
        putchar(((bits >> position) & UINT64_C(1)) ? '1' : '0');
    }
    putchar('\n');
}

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) {
        return 0;
    }

    uint64_t bits = 0;
    char command[16];

    for (int i = 0; i < q; i++) {
        if (scanf("%15s", command) != 1) {
            break;
        }

        if (strcmp(command, "SET") == 0) {
            int position;
            scanf("%d", &position);
            set_bit(&bits, position);
        } else if (strcmp(command, "CLEAR") == 0) {
            int position;
            scanf("%d", &position);
            clear_bit(&bits, position);
        } else if (strcmp(command, "FLIP") == 0) {
            int position;
            scanf("%d", &position);
            flip_bit(&bits, position);
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
