/*
 * P3 - Merge the Streams
 * Read the full statement in ..\problems\P3.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Starter functions:
 *   push - add an Item to the min-heap and bubble it up
 *   pop  - remove the smallest Item and sift the last Item down
 *
 * Suggested helper (write it yourself):
 *   comes_before(a, b) - true when a.value < b.value.
 *
 * The main() function already reads the lists, seeds the heap with each
 * list's first value, and performs the merge loop.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int list;
    int index;
} Item;

typedef struct {
    int *data;
    int length;
} List;

static void push(Item *heap, int *size, Item item) {
    /* TODO: append at heap[*size], increment *size, then bubble up by value */
    (void)heap;
    (void)size;
    (void)item;
}

static Item pop(Item *heap, int *size) {
    /* TODO: save the root, move the last Item to the root, decrement *size,
       then sift down by value */
    (void)heap;
    (void)size;
    Item empty = {0, 0, 0};
    return empty;
}

int main(void) {
    int k;
    if (scanf("%d", &k) != 1 || k <= 0) {
        return 0;
    }

    List *lists = (List *)calloc((size_t)k, sizeof(List));
    if (lists == NULL) {
        return 1;
    }

    int total = 0;

    for (int i = 0; i < k; i++) {
        int length;
        if (scanf("%d", &length) != 1 || length < 0) {
            length = 0;
        }

        lists[i].length = length;
        lists[i].data = NULL;

        if (length > 0) {
            lists[i].data = (int *)malloc((size_t)length * sizeof(int));
            if (lists[i].data == NULL) {
                fprintf(stderr, "out of memory\n");
                return 1;
            }
            for (int j = 0; j < length; j++) {
                scanf("%d", &lists[i].data[j]);
            }
            total += length;
        }
    }

    Item *heap = (Item *)malloc((size_t)(total > 0 ? total : 1) * sizeof(Item));
    if (heap == NULL) {
        return 1;
    }

    int heap_size = 0;

    for (int i = 0; i < k; i++) {
        if (lists[i].length > 0) {
            Item item = {lists[i].data[0], i, 0};
            push(heap, &heap_size, item);
        }
    }

    int first = 1;

    while (heap_size > 0) {
        Item item = pop(heap, &heap_size);

        if (!first) {
            putchar(' ');
        }
        printf("%d", item.value);
        first = 0;

        int next = item.index + 1;
        if (next < lists[item.list].length) {
            Item next_item = {lists[item.list].data[next], item.list, next};
            push(heap, &heap_size, next_item);
        }
    }
    putchar('\n');

    for (int i = 0; i < k; i++) {
        free(lists[i].data);
    }
    free(lists);
    free(heap);
    return 0;
}
