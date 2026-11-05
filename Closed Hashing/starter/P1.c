/*
 * P1 - Linear Probing Lot
 * Read the full statement in ..\problems\P1.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Starter functions:
 *   hash_key       - normalize key % M
 *   table_contains - check whether a key is already stored
 *   insert_linear  - place a key using linear probing
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

static int insert_linear(int *table, unsigned char *used, int m, int key) {
    /* TODO: probe (h + step) % m for step = 0..m-1.
       Store the key in the first empty slot and return that slot.
       Return -1 if the table is full. */
    int h = hash_key(key, m);
    (void)h;
    (void)table;
    (void)used;
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

    for (int i = 0; i < n; i++) {
        int key;
        if (scanf("%d", &key) != 1) {
            break;
        }

        if (!table_contains(table, used, m, key)) {
            insert_linear(table, used, m, key);
        }
    }

    print_table(table, used, m);

    free(table);
    free(used);
    return 0;
}
