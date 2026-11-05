/*
 * P3 - Double Trouble
 * Closed hashing with double hashing:
 *   h1(k) = k mod M
 *   h2(k) = 1 + (k mod (M - 1))
 *   slot  = (h1(k) + i * h2(k)) mod M
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 */

#include <stdio.h>
#include <stdlib.h>

static int hash_key(int key, int m) {
    int h = key % m;
    return h < 0 ? h + m : h;
}

static int hash_step(int key, int m) {
    int mod = m - 1;
    int h = key % mod;
    if (h < 0) {
        h += mod;
    }
    return 1 + h;
}

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2 || m < 2) {
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

        int h1 = hash_key(key, m);
        int h2 = hash_step(key, m);
        int placed = 0;

        for (int step = 0; step < m; step++) {
            int idx = (int)(((long long)h1 + (long long)step * h2) % m);
            if (!used[idx]) {
                used[idx] = 1;
                table[idx] = key;
                placed = 1;
                break;
            }
        }

        if (!placed) {
            printf("FAILED %d\n", key);
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
