/*
 * P3 - Word Watch
 * Read the full statement in ..\problems\P3.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Starter functions:
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
    /* TODO: copy at most size - 1 characters, convert letters with
       tolower(), and null-terminate the result */
    (void)source;
    (void)size;
    destination[0] = '\0';
}

static int hash_word(const char *word, int m) {
    /* TODO: return the sum of the ASCII values of word, modulo m */
    (void)word;
    (void)m;
    return 0;
}

static void add_word(Node **buckets, int m, const char *word) {
    /* TODO: search the word's chain. If found, increment count.
       Otherwise append a new node with count 1. */
    (void)buckets;
    (void)m;
    (void)word;
}

static void print_table(Node **buckets, int m) {
    /* TODO: print "i: word:count -> word:count" or "i: (empty)" */
    (void)buckets;
    (void)m;
}

static void free_table(Node **buckets, int m) {
    /* TODO: free every node in every chain */
    (void)buckets;
    (void)m;
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
