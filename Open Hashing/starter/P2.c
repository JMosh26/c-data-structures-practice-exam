/*
 * P2 - Lost and Found
 * Read the full statement in ..\problems\P2.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Starter functions:
 *   hash_key      - map a key to a bucket index
 *   contains      - check whether a key is already in a chain
 *   append        - add a key at the end of a chain
 *   find_position - return the 1-based chain position, or 0 if absent
 *   free_table    - release all chain nodes
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

static int hash_key(int key, int m) {
    /* TODO: return ((key % m) + m) % m */
    (void)key;
    (void)m;
    return 0;
}

static int contains(Node *head, int key) {
    /* TODO: walk the chain and return 1 if key is found, otherwise 0 */
    (void)head;
    (void)key;
    return 0;
}

static void append(Node **head, int key) {
    /* TODO: allocate a node and append it at the tail of the chain */
    (void)head;
    (void)key;
}

static int find_position(Node *head, int key) {
    /* TODO: return the 1-based position of key in the chain,
       or 0 if the key is not present */
    (void)head;
    (void)key;
    return 0;
}

static void free_table(Node **buckets, int m) {
    /* TODO: free every node in every chain */
    (void)buckets;
    (void)m;
}

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) {
        return 0;
    }

    Node **buckets = (Node **)calloc((size_t)m, sizeof(Node *));
    if (buckets == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int key;
        if (scanf("%d", &key) != 1) {
            break;
        }

        int h = hash_key(key, m);
        if (!contains(buckets[h], key)) {
            append(&buckets[h], key);
        }
    }

    int q;
    if (scanf("%d", &q) == 1) {
        for (int i = 0; i < q; i++) {
            int query;
            if (scanf("%d", &query) != 1) {
                break;
            }

            int h = hash_key(query, m);
            int position = find_position(buckets[h], query);

            if (position > 0) {
                printf("FOUND %d %d\n", h, position);
            } else {
                printf("NOT FOUND\n");
            }
        }
    }

    free_table(buckets, m);
    free(buckets);
    return 0;
}
