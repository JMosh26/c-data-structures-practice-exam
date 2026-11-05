/*
 * P3 - Word Watch
 * Answer key: open hashing used as a word-frequency table.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Solution functions:
 *   lowercase_copy - copy a word while converting it to lowercase
 *   hash_word      - sum the lowercase ASCII values and take the remainder
 *   add_word       - update a count or append a new chain node
 *   print_table    - print every bucket and chain
 *   free_table     - release all chain nodes
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 32

typedef struct Node {
    char word[MAX_WORD];
    int count;
    struct Node *next;
} Node;

static void lowercase_copy(char *destination, const char *source, size_t size) {
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

static int hash_word(const char *word, int m) {
    unsigned long sum = 0;

    for (const unsigned char *p = (const unsigned char *)word; *p != '\0'; p++) {
        sum += *p;
    }

    return (int)(sum % (unsigned long)m);
}

static void add_word(Node **buckets, int m, const char *word) {
    int h = hash_word(word, m);

    for (Node *cur = buckets[h]; cur != NULL; cur = cur->next) {
        if (strcmp(cur->word, word) == 0) {
            cur->count++;
            return;
        }
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    strcpy(node->word, word);
    node->count = 1;
    node->next = NULL;

    if (buckets[h] == NULL) {
        buckets[h] = node;
        return;
    }

    Node *cur = buckets[h];
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
            printf(" %s:%d", cur->word, cur->count);
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
    int m;
    if (scanf("%d", &m) != 1 || m <= 0) {
        return 0;
    }

    Node **buckets = (Node **)calloc((size_t)m, sizeof(Node *));
    if (buckets == NULL) {
        return 1;
    }

    char raw[128];
    char word[MAX_WORD] = {0};

    while (scanf("%127s", raw) == 1) {
        lowercase_copy(word, raw, sizeof(word));
        add_word(buckets, m, word);
    }

    print_table(buckets, m);

    free_table(buckets, m);
    free(buckets);
    return 0;
}
