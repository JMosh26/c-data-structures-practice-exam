/*
 * P1 - Linear Probing Lot
 * Answer key: closed hashing with linear probing.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
 *   hash_key       - normalize key % M
 *   table_contains - check whether a key is already stored
 *   insert_linear  - place a key using linear probing
 *   print_table    - print every slot
 */

#include <stdio.h>
#include <stdlib.h>

static int hash_key(int key, int m) {
    int h = key % m;
    return h < 0 ? h + m : h;
}

static int table_contains(const int *table, const unsigned char *used, int m, int key) {
    for (int i = 0; i < m; i++) {
        if (used[i] && table[i] == key) {
            return 1;
        }
    }
    return 0;
}

static int insert_linear(int *table, unsigned char *used, int m, int key) {
    int h = hash_key(key, m);

    for (int step = 0; step < m; step++) {
        int index = (h + step) % m;
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
            printf("%d: (empty)\n", i);
        }
    }
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
