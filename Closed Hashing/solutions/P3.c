/*
 * P3 - Double Trouble
 * Answer key: closed hashing with double hashing.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Solution functions:
 *   hash_key       - compute h1(k)
 *   hash_step      - compute h2(k), which is never zero
 *   table_contains - check whether a key is already stored
 *   insert_double  - place a key using double hashing
 *   print_table    - print every slot
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

static int table_contains(const int *table, const unsigned char *used, int m, int key) {
    for (int i = 0; i < m; i++) {
        if (used[i] && table[i] == key) {
            return 1;
        }
    }
    return 0;
}

static int insert_double(int *table, unsigned char *used, int m, int key) {
    int h1 = hash_key(key, m);
    int h2 = hash_step(key, m);

    for (int step = 0; step < m; step++) {
        int index = (int)(((long long)h1 + (long long)step * h2) % m);

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
