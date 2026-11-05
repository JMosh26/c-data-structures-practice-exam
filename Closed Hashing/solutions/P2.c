/*
 * P2 - Vault Codes
 * Answer key: quadratic probing with printed probe paths.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Solution functions:
 *   hash_key         - normalize key % M
 *   find_quadratic   - search a quadratic probe path
 *   insert_quadratic - place a key and record the path
 *   print_table      - print every slot
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SLOTS 1000

static int hash_key(int key, int m) {
    int h = key % m;
    return h < 0 ? h + m : h;
}

static int find_quadratic(const int *table, const unsigned char *used, int m, int key, int *probes) {
    int h = hash_key(key, m);
    *probes = 0;

    for (int step = 0; step < m; step++) {
        int index = (int)(((long long)h + (long long)step * step) % m);
        (*probes)++;

        if (!used[index]) {
            return -1;
        }
        if (table[index] == key) {
            return index;
        }
    }

    return -1;
}

static int insert_quadratic(int *table, unsigned char *used, int m, int key,
                            int *path, int *path_length, int *probes) {
    int h = hash_key(key, m);
    *path_length = 0;
    *probes = 0;

    for (int step = 0; step < m; step++) {
        int index = (int)(((long long)h + (long long)step * step) % m);
        path[(*path_length)++] = index;
        (*probes)++;

        if (!used[index]) {
            used[index] = 1;
            table[index] = key;
            return index;
        }
    }

    return -1;
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

        int probes = 0;
        int slot = find_quadratic(table, used, m, key, &probes);
        total_probes += probes;

        if (slot >= 0) {
            printf("%d: DUP at %d\n", key, slot);
            continue;
        }

        int path[MAX_SLOTS];
        int path_length = 0;
        slot = insert_quadratic(table, used, m, key, path, &path_length, &probes);
        total_probes += probes;

        printf("%d:", key);
        for (int j = 0; j < path_length; j++) {
            printf(" %d", path[j]);
            if (j + 1 < path_length) {
                printf(" ->");
            }
        }
        if (slot < 0) {
            printf(" -> FAIL");
        }
        printf("\n");
    }

    printf("table:\n");
    print_table(table, used, m);
    printf("probes: %lld\n", total_probes);

    free(table);
    free(used);
    return 0;
}
