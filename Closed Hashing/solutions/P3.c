/*
 * P3 - Ghost Gallery
 * Answer key: double hashing with tombstones and live operations.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Solution functions:
 *   hash1        - primary hash h1(k)
 *   hash2        - secondary hash h2(k), never zero
 *   find_slot    - locate a live key along the double-hash probe path
 *   insert_key   - add a key, reusing the first tombstone
 *   delete_key   - turn a live key into a tombstone
 *   print_table  - print every slot
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define OCCUPIED 1
#define TOMBSTONE 2

static int hash1(int key, int m) {
    int h = key % m;
    return h < 0 ? h + m : h;
}

static int hash2(int key, int m) {
    int mod = m - 1;
    int h = key % mod;
    if (h < 0) {
        h += mod;
    }
    return 1 + h;
}

static int find_slot(const int *table, const unsigned char *state, int m, int key, int *probes) {
    int h = hash1(key, m);
    int step = hash2(key, m);
    *probes = 0;

    for (int i = 0; i < m; i++) {
        int index = (int)(((long long)h + (long long)i * step) % m);
        (*probes)++;

        if (state[index] == EMPTY) {
            return -1;
        }
        if (state[index] == OCCUPIED && table[index] == key) {
            return index;
        }
    }

    return -1;
}

/*
 * Returns:
 *   0 = inserted at *slot
 *   1 = key already exists at *slot
 *   2 = table full
 */
static int insert_key(int *table, unsigned char *state, int m, int key, int *slot) {
    int h = hash1(key, m);
    int step = hash2(key, m);
    int first_tombstone = -1;

    for (int i = 0; i < m; i++) {
        int index = (int)(((long long)h + (long long)i * step) % m);

        if (state[index] == OCCUPIED) {
            if (table[index] == key) {
                *slot = index;
                return 1;
            }
        } else if (state[index] == TOMBSTONE) {
            if (first_tombstone < 0) {
                first_tombstone = index;
            }
        } else {
            int target = first_tombstone >= 0 ? first_tombstone : index;
            table[target] = key;
            state[target] = OCCUPIED;
            *slot = target;
            return 0;
        }
    }

    if (first_tombstone >= 0) {
        table[first_tombstone] = key;
        state[first_tombstone] = OCCUPIED;
        *slot = first_tombstone;
        return 0;
    }

    return 2;
}

static int delete_key(int *table, unsigned char *state, int m, int key, int *slot) {
    int probes = 0;
    int found = find_slot(table, state, m, key, &probes);

    if (found < 0) {
        return -1;
    }

    state[found] = TOMBSTONE;
    *slot = found;
    return 0;
}

static void print_table(const int *table, const unsigned char *state, int m) {
    for (int i = 0; i < m; i++) {
        if (state[i] == OCCUPIED) {
            printf("%d: %d\n", i, table[i]);
        } else if (state[i] == TOMBSTONE) {
            printf("%d: tomb\n", i);
        } else {
            printf("%d: empty\n", i);
        }
    }
}

int main(void) {
    int m, q;
    if (scanf("%d %d", &m, &q) != 2 || m < 2) {
        return 0;
    }

    int *table = (int *)calloc((size_t)m, sizeof(int));
    unsigned char *state = (unsigned char *)calloc((size_t)m, sizeof(unsigned char));
    if (table == NULL || state == NULL) {
        free(table);
        free(state);
        return 1;
    }

    int count = 0;
    char command[16];

    for (int i = 0; i < q; i++) {
        if (scanf("%15s", command) != 1) {
            break;
        }

        if (strcmp(command, "ADD") == 0) {
            int key;
            scanf("%d", &key);

            int slot = -1;
            int result = insert_key(table, state, m, key, &slot);
            if (result == 0) {
                count++;
                printf("ADDED %d\n", slot);
            } else if (result == 1) {
                printf("EXISTS\n");
            } else {
                printf("FULL\n");
            }
        } else if (strcmp(command, "DEL") == 0) {
            int key;
            scanf("%d", &key);

            int slot = -1;
            if (delete_key(table, state, m, key, &slot) == 0) {
                count--;
                printf("DELETED %d\n", slot);
            } else {
                printf("MISSING\n");
            }
        } else if (strcmp(command, "HAS") == 0) {
            int key;
            scanf("%d", &key);

            int probes = 0;
            int slot = find_slot(table, state, m, key, &probes);
            if (slot >= 0) {
                printf("YES %d\n", slot);
            } else {
                printf("NO\n");
            }
        } else if (strcmp(command, "COUNT") == 0) {
            printf("%d\n", count);
        } else if (strcmp(command, "PRINT") == 0) {
            print_table(table, state, m);
        }
    }

    free(table);
    free(state);
    return 0;
}
