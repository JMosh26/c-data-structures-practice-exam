/*
 * P3 - Tag Tournament
 * Answer key: case-insensitive open hashing plus a top-K ranking.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Solution functions:
 *   normalize    - copy a tag while converting it to lowercase
 *   hash_tag     - sum the lowercase ASCII values and take the remainder
 *   add_tag      - update a count or insert a new chain node
 *   collect_tags - gather every node pointer into an array
 *   compare_tags - order by count descending, then tag ascending
 *   print_top    - print the first K ranked tags
 *   free_table   - release all chain nodes
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAG 64

typedef struct Node {
    char tag[MAX_TAG];
    int count;
    struct Node *next;
} Node;

static void normalize(char *destination, const char *source, size_t size) {
    if (size == 0) {
        return;
    }

    size_t i = 0;
    while (source[i] != '\0' && i + 1 < size) {
        destination[i] = (char)tolower((unsigned char)source[i]);
        i++;
    }
    destination[i] = '\0';
}

static int hash_tag(const char *tag, int m) {
    unsigned long sum = 0;

    for (const unsigned char *p = (const unsigned char *)tag; *p != '\0'; p++) {
        sum += *p;
    }

    return (int)(sum % (unsigned long)m);
}

static void add_tag(Node **buckets, int m, const char *tag) {
    int h = hash_tag(tag, m);

    for (Node *cur = buckets[h]; cur != NULL; cur = cur->next) {
        if (strcmp(cur->tag, tag) == 0) {
            cur->count++;
            return;
        }
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    strcpy(node->tag, tag);
    node->count = 1;
    node->next = buckets[h];
    buckets[h] = node;
}

static int collect_tags(Node **buckets, int m, Node **out) {
    int total = 0;

    for (int i = 0; i < m; i++) {
        for (Node *cur = buckets[i]; cur != NULL; cur = cur->next) {
            out[total++] = cur;
        }
    }

    return total;
}

static int compare_tags(const void *a, const void *b) {
    const Node *left = *(const Node *const *)a;
    const Node *right = *(const Node *const *)b;

    if (left->count != right->count) {
        return right->count - left->count;
    }

    return strcmp(left->tag, right->tag);
}

static void print_top(Node **items, int count, int k) {
    if (count == 0 || k <= 0) {
        printf("(none)\n");
        return;
    }

    int limit = k < count ? k : count;

    for (int i = 0; i < limit; i++) {
        printf("%s %d\n", items[i]->tag, items[i]->count);
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
    int m, k;
    if (scanf("%d %d", &m, &k) != 2 || m <= 0) {
        return 0;
    }

    Node **buckets = (Node **)calloc((size_t)m, sizeof(Node *));
    if (buckets == NULL) {
        return 1;
    }

    char raw[128];
    char tag[MAX_TAG];
    int total = 0;

    while (scanf("%127s", raw) == 1) {
        normalize(tag, raw, sizeof(tag));
        add_tag(buckets, m, tag);
        total++;
    }

    Node **items = (Node **)malloc((size_t)(total > 0 ? total : 1) * sizeof(Node *));
    if (items == NULL) {
        free_table(buckets, m);
        free(buckets);
        return 1;
    }

    int unique = collect_tags(buckets, m, items);
    qsort(items, (size_t)unique, sizeof(Node *), compare_tags);
    print_top(items, unique, k);

    free(items);
    free_table(buckets, m);
    free(buckets);
    return 0;
}
