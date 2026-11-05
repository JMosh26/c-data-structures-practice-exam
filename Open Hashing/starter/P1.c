/*
 * P1 - Bucket Brigade
 * Read the full statement in ..\problems\P1.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Starter functions:
 *   hash_key     - map a key to a bucket index
 *   contains     - check whether a key is already in a chain
 *   append       - add a key at the end of a chain
 *   print_table  - print every bucket
 *   free_table   - release all chain nodes
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
    /* TODO: allocate a node, set its key and next pointer, and append it
       at the tail so insertion order is preserved */
    (void)head;
    (void)key;
}

static void print_table(Node **buckets, int m) {
    /* TODO: for each bucket print "i: k1 -> k2" or "i: (empty)" */
    (void)buckets;
    (void)m;
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

    print_table(buckets, m);

    free_table(buckets, m);
    free(buckets);
    return 0;
}
