/*
 * P2 - Vault Codes
 * Read the full statement in ..\problems\P2.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Starter functions:
 *   hash_key         - normalize key % M
 *   find_quadratic   - search a quadratic probe path
 *   insert_quadratic - place a key and record the path
 *   print_table      - print every slot
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SLOTS 1000

static int hash_key(int key, int m) {
    /* TODO: return ((key % m) + m) % m */
    (void)key;
    (void)m;
    return 0;
}

static int find_quadratic(const int *table, const unsigned char *used, int m, int key, int *probes) {
    /* TODO: follow (h + step * step) % m until an empty slot or the key.
       Count every slot examined in *probes. Return the slot or -1. */
    (void)table;
    (void)used;
    (void)m;
    (void)key;
    (void)probes;
    return -1;
}

static int insert_quadratic(int *table, unsigned char *used, int m, int key,
                            int *path, int *path_length, int *probes) {
    /* TODO: follow the same probe path, append every visited slot to path,
       and place the key in the first empty slot. Return the slot or -1. */
    (void)table;
    (void)used;
    (void)m;
    (void)key;
    (void)path;
    (void)path_length;
    (void)probes;
    return -1;
}

static void print_table(const int *table, const unsigned char *used, int m) {
    /* TODO: print "i: key" for occupied slots and "i: empty" otherwise */
    (void)table;
    (void)used;
    (void)m;
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
