/*
 * P1 - Locker Loop
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
 *   push_front   - add a key at the front of a chain
 *   chain_length - count the nodes in one chain
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

static void push_front(Node **head, int key) {
    /* TODO: allocate a node, store the key, link it before the old head,
       and update *head */
    (void)head;
    (void)key;
}

static int chain_length(Node *head) {
    /* TODO: count and return the nodes in this chain */
    (void)head;
    return 0;
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
    if (scanf("%d %d", &m, &n) != 2 || m <= 0) {
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
            push_front(&buckets[h], key);
        }
    }

    print_table(buckets, m);

    int empty = 0;
    int chains = 0;
    int longest = 0;

    for (int i = 0; i < m; i++) {
        int length = chain_length(buckets[i]);
        if (length == 0) {
            empty++;
        } else {
            chains++;
            if (length > longest) {
                longest = length;
            }
        }
    }

    printf("empty: %d\n", empty);
    printf("chains: %d\n", chains);
    printf("longest: %d\n", longest);

    free_table(buckets, m);
    free(buckets);
    return 0;
}
