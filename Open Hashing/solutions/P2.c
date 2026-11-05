/*
 * P2 - Lost and Found
 * Answer key: open hashing with separate chaining and search queries.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Solution functions:
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

static int find_position(Node *head, int key) {
    int position = 0;

    for (Node *cur = head; cur != NULL; cur = cur->next) {
        position++;
        if (cur->key == key) {
            return position;
        }
    }
    return 0;
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
