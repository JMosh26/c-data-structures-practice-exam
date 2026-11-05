/*
 * P1 - Bucket Brigade
 * Answer key: open hashing with separate chaining.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
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
    int h = key % m;
    return h < 0 ? h + m : h;
}

static int contains(Node *head, int key) {
    for (Node *cur = head; cur != NULL; cur = cur->next) {
        if (cur->key == key) {
            return 1;
        }
    }
    return 0;
}

static void append(Node **head, int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    node->key = key;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
        return;
    }

    Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
}

static void print_table(Node **buckets, int m) {
    for (int i = 0; i < m; i++) {
        printf("%d:", i);

        if (buckets[i] == NULL) {
            printf(" (empty)\n");
            continue;
        }

        for (Node *cur = buckets[i]; cur != NULL; cur = cur->next) {
            printf(" %d", cur->key);
            if (cur->next != NULL) {
                printf(" ->");
            }
        }
        printf("\n");
    }
}

static void free_table(Node **buckets, int m) {
    for (int i = 0; i < m; i++) {
        while (buckets[i] != NULL) {
            Node *tmp = buckets[i];
            buckets[i] = tmp->next;
            free(tmp);
        }
    }
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
