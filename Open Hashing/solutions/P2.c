/*
 * P2 - Lost and Found
 * Open hashing (separate chaining): insert keys, then answer search queries.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
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
            int key;
            if (scanf("%d", &key) != 1) {
                break;
            }
            int h = hash_key(key, m);
            int position = 0;
            int found = 0;

            for (Node *cur = buckets[h]; cur != NULL; cur = cur->next) {
                position++;
                if (cur->key == key) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("FOUND %d %d\n", h, position);
            } else {
                printf("NOT FOUND\n");
            }
        }
    }

    for (int i = 0; i < m; i++) {
        while (buckets[i] != NULL) {
            Node *tmp = buckets[i];
            buckets[i] = tmp->next;
            free(tmp);
        }
    }
    free(buckets);
    return 0;
}
