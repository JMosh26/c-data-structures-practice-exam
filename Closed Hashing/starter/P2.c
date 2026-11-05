/*
 * P2 - Quadratic Quest
 * Read the full statement in ..\problems\P2.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Starter functions:
 *   hash_key       - normalize key % M
 *   table_contains - check whether a key is already stored
 *   insert_quadratic - place a key and count the probes
 *   print_table    - print every slot
 */

#include <stdio.h>
#include <stdlib.h>

static int hash_key(int key, int m) {
    /* TODO: return ((key % m) + m) % m */
    (void)key;
    (void)m;
    return 0;
}

static int table_contains(const int *table, const unsigned char *used, int m, int key) {
    /* TODO: scan the table and return 1 if used[j] is set and table[j] == key */
    (void)table;
    (void)used;
    (void)m;
    (void)key;
    return 0;
}

static int insert_quadratic(int *table, unsigned char *used, int m, int key, int *probes) {
    /* TODO: probe (h + i*i) % m for i = 0..m-1.
       Add 1 to *probes for every slot examined.
       Return the slot where the key was placed, or -1 if it could not be placed. */
    int h = hash_key(key, m);
    (void)h;
    (void)table;
    (void)used;
    *probes = 0;
    return 0;
}

static void print_table(const int *table, const unsigned char *used, int m) {
    /* TODO: print "i: key" for occupied slots and "i: (empty)" otherwise */
    (void)table;
    (void)used;
    (void)m;
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

    int total_probes = 0;

    for (int i = 0; i < n; i++) {
        int key;
        if (scanf("%d", &key) != 1) {
            break;
        }

        if (table_contains(table, used, m, key)) {
            continue;
        }

        int probes = 0;
        int slot = insert_quadratic(table, used, m, key, &probes);
        total_probes += probes;

        if (slot < 0) {
            printf("FAILED %d\n", key);
        }
    }

    printf("probes: %d\n", total_probes);
    print_table(table, used, m);

    free(table);
    free(used);
    return 0;
}
