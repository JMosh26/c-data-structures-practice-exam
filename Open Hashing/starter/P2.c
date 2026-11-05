/*
 * P2 - Reunion Registry
 * Read the full statement in ..\problems\P2.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Starter functions:
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
    /* TODO: sum (i + 1) * (unsigned char)name[i] and return sum % m */
    (void)name;
    (void)m;
    return 0;
}

static Node *find_node(Node *head, const char *name) {
    /* TODO: walk the chain with strcmp and return the matching node */
    (void)head;
    (void)name;
    return NULL;
}

static void append(Node **head, const char *name) {
    /* TODO: allocate a node, copy the name, and append it at the tail */
    (void)head;
    (void)name;
}

static int remove_name(Node **head, const char *name) {
    /* TODO: unlink the matching node and free it; return 1 if removed */
    (void)head;
    (void)name;
    return 0;
}

static int find_position(Node *head, const char *name) {
    /* TODO: return the 1-based position of name, or 0 if absent */
    (void)head;
    (void)name;
    return 0;
}

static int count_nodes(Node **buckets, int m) {
    /* TODO: count every node in every bucket */
    (void)buckets;
    (void)m;
    return 0;
}

static void print_table(Node **buckets, int m) {
    /* TODO: print "i: name1 -> name2" or "i: (empty)" for every bucket */
    (void)buckets;
    (void)m;
}

static void free_table(Node **buckets, int m) {
    /* TODO: free every node in every chain */
    (void)buckets;
    (void)m;
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
