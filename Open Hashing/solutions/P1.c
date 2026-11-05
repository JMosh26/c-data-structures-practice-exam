/*
 * P1 - Locker Loop
 * Answer key: open hashing with head insertion and chain statistics.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
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

static void push_front(Node **head, int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    node->key = key;
    node->next = *head;
    *head = node;
}

static int chain_length(Node *head) {
    int length = 0;

    for (Node *cur = head; cur != NULL; cur = cur->next) {
        length++;
    }

    return length;
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
