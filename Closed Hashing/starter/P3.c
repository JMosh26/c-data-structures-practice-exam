/*
 * P3 - Ghost Gallery
 * Read the full statement in ..\problems\P3.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Starter functions:
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
    /* TODO: return ((key % m) + m) % m */
    (void)key;
    (void)m;
    return 0;
}

static int hash2(int key, int m) {
    /* TODO: return 1 + (((key % (m - 1)) + (m - 1)) % (m - 1)) */
    (void)key;
    (void)m;
    return 1;
}

static int find_slot(const int *table, const unsigned char *state, int m, int key, int *probes) {
    /* TODO: follow (h1 + i * h2) % m. Stop at EMPTY, return OCCUPIED matches.
       Count every examined slot in *probes. */
    (void)table;
    (void)state;
    (void)m;
    (void)key;
    (void)probes;
    return -1;
}

/*
 * Returns:
 *   0 = inserted at *slot
 *   1 = key already exists at *slot
 *   2 = table full
 */
static int insert_key(int *table, unsigned char *state, int m, int key, int *slot) {
    /* TODO: probe once, remember the first TOMBSTONE, and insert there
       if no EMPTY slot is found first. */
    (void)table;
    (void)state;
    (void)m;
    (void)key;
    (void)slot;
    return 2;
}

static int delete_key(int *table, unsigned char *state, int m, int key, int *slot) {
    /* TODO: find the live key and turn its state into TOMBSTONE */
    (void)table;
    (void)state;
    (void)m;
    (void)key;
    (void)slot;
    return -1;
}

static void print_table(const int *table, const unsigned char *state, int m) {
    /* TODO: print "i: key", "i: tomb", or "i: empty" for every slot */
    (void)table;
    (void)state;
    (void)m;
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
