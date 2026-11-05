/*
 * P1 - Bit Vector Playground
 * A 64-bit vector with SET / CLEAR / FLIP / GET / COUNT / PRINT commands.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
            if (position >= 0 && position < 64) {
                bits |= UINT64_C(1) << position;
            }
        } else if (strcmp(command, "CLEAR") == 0) {
            int position;
            scanf("%d", &position);
            if (position >= 0 && position < 64) {
                bits &= ~(UINT64_C(1) << position);
            }
        } else if (strcmp(command, "FLIP") == 0) {
            int position;
            scanf("%d", &position);
            if (position >= 0 && position < 64) {
                bits ^= UINT64_C(1) << position;
            }
        } else if (strcmp(command, "GET") == 0) {
            int position;
            scanf("%d", &position);
            if (position >= 0 && position < 64) {
                int value = (int)((bits >> position) & UINT64_C(1));
                printf("bit %d = %d\n", position, value);
            }
        } else if (strcmp(command, "COUNT") == 0) {
            printf("%d\n", __builtin_popcountll(bits));
        } else if (strcmp(command, "PRINT") == 0) {
            for (int position = 63; position >= 0; position--) {
                putchar(((bits >> position) & UINT64_C(1)) ? '1' : '0');
            }
            putchar('\n');
        }
    }

    return 0;
}
