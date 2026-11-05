/*
 * P3 - Tag Tournament
 * Read the full statement in ..\problems\P3.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Starter functions:
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
    /* TODO: copy source into destination, lowercasing each character */
    (void)destination;
    (void)source;
    (void)size;
}

static int hash_tag(const char *tag, int m) {
    /* TODO: return the sum of the lowercase ASCII values modulo m */
    (void)tag;
    (void)m;
    return 0;
}

static void add_tag(Node **buckets, int m, const char *tag) {
    /* TODO: find the tag and increment its count, or insert a new node */
    (void)buckets;
    (void)m;
    (void)tag;
}

static int collect_tags(Node **buckets, int m, Node **out) {
    /* TODO: store every node pointer in out and return the total */
    (void)buckets;
    (void)m;
    (void)out;
    return 0;
}

static int compare_tags(const void *a, const void *b) {
    /* TODO: count descending, then tag ascending with strcmp */
    (void)a;
    (void)b;
    return 0;
}

static void print_top(Node **items, int count, int k) {
    /* TODO: print the first min(k, count) ranked tags, or "(none)" */
    (void)items;
    (void)count;
    (void)k;
}

static void free_table(Node **buckets, int m) {
    /* TODO: free every node in every chain */
    (void)buckets;
    (void)m;
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
