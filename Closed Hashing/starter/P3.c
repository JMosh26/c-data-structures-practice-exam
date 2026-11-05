/*
 * P3 - Double Trouble
 * Read the full statement in ..\problems\P3.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Starter functions:
 *   hash_key       - compute h1(k)
 *   hash_step      - compute h2(k), which is never zero
 *   table_contains - check whether a key is already stored
 *   insert_double  - place a key using double hashing
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

static int hash_step(int key, int m) {
    /* TODO: return 1 + normalized(key % (m - 1)) */
    (void)key;
    (void)m;
    return 1;
}

static int table_contains(const int *table, const unsigned char *used, int m, int key) {
    /* TODO: scan the table and return 1 if used[j] is set and table[j] == key */
    (void)table;
    (void)used;
    (void)m;
    (void)key;
    return 0;
}

static int insert_double(int *table, unsigned char *used, int m, int key) {
    /* TODO: probe (h1 + i*h2) % m for i = 0..m-1.
       Return the slot where the key was placed, or -1 if it could not be placed. */
    int h1 = hash_key(key, m);
    int h2 = hash_step(key, m);
    (void)h1;
    (void)h2;
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

        if (table_contains(table, used, m, key)) {
            continue;
        }

        if (insert_double(table, used, m, key) < 0) {
            printf("FAILED %d\n", key);
        }
    }

    print_table(table, used, m);

    free(table);
    free(used);
    return 0;
}
