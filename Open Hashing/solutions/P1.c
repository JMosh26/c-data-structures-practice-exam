/*
 * P1 - Bucket Brigade
 * Open hashing (separate chaining): insert keys, then print every bucket.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
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

    for (int i = 0; i < m; i++) {
        printf("%d:", i);
        if (buckets[i] == NULL) {
            printf(" (empty)\n");
        } else {
            for (Node *cur = buckets[i]; cur != NULL; cur = cur->next) {
                printf(" %d", cur->key);
                if (cur->next != NULL) {
                    printf(" ->");
                }
            }
            printf("\n");
        }

        while (buckets[i] != NULL) {
            Node *tmp = buckets[i];
            buckets[i] = tmp->next;
            free(tmp);
        }
    }

    free(buckets);
    return 0;
}
