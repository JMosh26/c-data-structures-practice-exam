/*
 * P1 - Linear Probing Lot
 * Closed hashing (open addressing) with linear probing.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 */

#include <stdio.h>
#include <stdlib.h>

static int hash_key(int key, int m) {
    int h = key % m;
    return h < 0 ? h + m : h;
}

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) {
        return 0;
    }

    int *table = (int *)calloc((size_t)m, sizeof(int));
    unsigned char *used = (unsigned char *)calloc((size_t)m, sizeof(unsigned char));
    if (table == NULL || used == NULL) {
        free(table);
        free(used);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int key;
        if (scanf("%d", &key) != 1) {
            break;
        }

        /* Ignore a key that is already stored. */
        int duplicate = 0;
        for (int j = 0; j < m; j++) {
            if (used[j] && table[j] == key) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            continue;
        }

        int h = hash_key(key, m);
        for (int step = 0; step < m; step++) {
            int idx = (h + step) % m;
            if (!used[idx]) {
                used[idx] = 1;
                table[idx] = key;
                break;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (used[i]) {
            printf("%d: %d\n", i, table[i]);
        } else {
            printf("%d: (empty)\n", i);
        }
    }

    free(table);
    free(used);
    return 0;
}
