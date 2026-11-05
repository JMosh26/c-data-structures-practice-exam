/*
 * P1 - Parking Lot
 * Answer key: closed hashing with linear probing and per-operation status.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
 *   hash_key     - normalize key % M
 *   park         - probe once, report parked / duplicate / full
 *   print_table  - print every slot
 */

#include <stdio.h>
#include <stdlib.h>

static int hash_key(int key, int m) {
    int h = key % m;
    return h < 0 ? h + m : h;
}

/*
 * Returns:
 *   0 = parked at *slot
 *   1 = key already present at *slot
 *   2 = table full
 * *probes receives the number of slots examined.
 */
static int park(int *table, unsigned char *used, int m, int key, int *slot, int *probes) {
    int h = hash_key(key, m);
    *probes = 0;

    for (int step = 0; step < m; step++) {
        int index = (h + step) % m;
        (*probes)++;

        if (used[index]) {
            if (table[index] == key) {
                *slot = index;
                return 1;
            }
        } else {
            used[index] = 1;
            table[index] = key;
            *slot = index;
            return 0;
        }
    }

    return 2;
}

static void print_table(const int *table, const unsigned char *used, int m) {
    for (int i = 0; i < m; i++) {
        if (used[i]) {
            printf("%d: %d\n", i, table[i]);
        } else {
            printf("%d: empty\n", i);
        }
    }
}

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2 || m <= 0) {
        return 0;
    }

    int *table = (int *)calloc((size_t)m, sizeof(int));
    unsigned char *used = (unsigned char *)calloc((size_t)m, sizeof(unsigned char));
    if (table == NULL || used == NULL) {
        free(table);
        free(used);
        return 1;
    }

    long long total_probes = 0;

    for (int i = 0; i < n; i++) {
        int key;
        if (scanf("%d", &key) != 1) {
            break;
        }

        int slot = -1;
        int probes = 0;
        int result = park(table, used, m, key, &slot, &probes);
        total_probes += probes;

        if (result == 0) {
            printf("PARKED %d\n", slot);
        } else if (result == 1) {
            printf("ALREADY %d\n", slot);
        } else {
            printf("FULL\n");
        }
    }

    printf("table:\n");
    print_table(table, used, m);
    printf("probes: %lld\n", total_probes);

    free(table);
    free(used);
    return 0;
}
