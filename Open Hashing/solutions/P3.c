/*
 * P3 - Word Watch
 * Open hashing (separate chaining) used as a word-frequency table.
 * Hash function: sum of the lowercase ASCII codes, modulo M.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
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

static int hash_word(const char *s, int m) {
    unsigned long sum = 0;
    for (const unsigned char *p = (const unsigned char *)s; *p != '\0'; p++) {
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
    } else {
        Node *cur = buckets[h];
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = node;
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
    char word[MAX_WORD];
    while (scanf("%127s", raw) == 1) {
        size_t len = 0;
        for (size_t i = 0; raw[i] != '\0' && len < MAX_WORD - 1; i++) {
            word[len++] = (char)tolower((unsigned char)raw[i]);
        }
        word[len] = '\0';
        if (len > 0) {
            add_word(buckets, m, word);
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d:", i);
        if (buckets[i] == NULL) {
            printf(" (empty)\n");
        } else {
            for (Node *cur = buckets[i]; cur != NULL; cur = cur->next) {
                printf(" %s:%d", cur->word, cur->count);
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
