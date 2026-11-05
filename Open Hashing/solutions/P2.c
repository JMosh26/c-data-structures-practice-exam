/*
 * P2 - Reunion Registry
 * Answer key: open hashing with string keys, weighted hashing, and deletion.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Solution functions:
 *   hash_name     - weighted character sum modulo M
 *   find_node     - return the node holding a name, or NULL
 *   append        - add a name at the end of a chain
 *   remove_name   - unlink a name and free its node
 *   find_position - return the 1-based chain position, or 0
 *   count_nodes   - count all names in the table
 *   print_table   - print every bucket and chain
 *   free_table    - release all chain nodes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 32

typedef struct Node {
    char name[MAX_NAME];
    struct Node *next;
} Node;

static int hash_name(const char *name, int m) {
    unsigned long long sum = 0;

    for (int i = 0; name[i] != '\0'; i++) {
        sum += (unsigned long long)(i + 1) * (unsigned char)name[i];
    }

    return (int)(sum % (unsigned long long)m);
}

static Node *find_node(Node *head, const char *name) {
    for (Node *cur = head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->name, name) == 0) {
            return cur;
        }
    }
    return NULL;
}

static void append(Node **head, const char *name) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    strcpy(node->name, name);
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

static int remove_name(Node **head, const char *name) {
    Node **trav = head;

    while (*trav != NULL && strcmp((*trav)->name, name) != 0) {
        trav = &(*trav)->next;
    }

    if (*trav == NULL) {
        return 0;
    }

    Node *tmp = *trav;
    *trav = tmp->next;
    free(tmp);
    return 1;
}

static int find_position(Node *head, const char *name) {
    int position = 0;

    for (Node *cur = head; cur != NULL; cur = cur->next) {
        position++;
        if (strcmp(cur->name, name) == 0) {
            return position;
        }
    }

    return 0;
}

static int count_nodes(Node **buckets, int m) {
    int total = 0;

    for (int i = 0; i < m; i++) {
        for (Node *cur = buckets[i]; cur != NULL; cur = cur->next) {
            total++;
        }
    }

    return total;
}

static void print_table(Node **buckets, int m) {
    for (int i = 0; i < m; i++) {
        printf("%d:", i);

        if (buckets[i] == NULL) {
            printf(" (empty)\n");
            continue;
        }

        for (Node *cur = buckets[i]; cur != NULL; cur = cur->next) {
            printf(" %s", cur->name);
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
    int m, q;
    if (scanf("%d %d", &m, &q) != 2 || m <= 0) {
        return 0;
    }

    Node **buckets = (Node **)calloc((size_t)m, sizeof(Node *));
    if (buckets == NULL) {
        return 1;
    }

    char command[16];
    char name[MAX_NAME];

    for (int i = 0; i < q; i++) {
        if (scanf("%15s", command) != 1) {
            break;
        }

        if (strcmp(command, "ADD") == 0) {
            scanf("%31s", name);
            int h = hash_name(name, m);
            if (find_node(buckets[h], name) == NULL) {
                append(&buckets[h], name);
            }
        } else if (strcmp(command, "DEL") == 0) {
            scanf("%31s", name);
            int h = hash_name(name, m);
            printf("%s\n", remove_name(&buckets[h], name) ? "REMOVED" : "MISSING");
        } else if (strcmp(command, "FIND") == 0) {
            scanf("%31s", name);
            int h = hash_name(name, m);
            int position = find_position(buckets[h], name);
            if (position > 0) {
                printf("FOUND %d %d\n", h, position);
            } else {
                printf("NOT FOUND\n");
            }
        } else if (strcmp(command, "COUNT") == 0) {
            printf("%d\n", count_nodes(buckets, m));
        } else if (strcmp(command, "PRINT") == 0) {
            print_table(buckets, m);
        }
    }

    free_table(buckets, m);
    free(buckets);
    return 0;
}
