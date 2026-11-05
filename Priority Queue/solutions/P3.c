/*
 * P3 - Stream Merger
 * Answer key: merge K non-increasing streams with a max-heap.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
 * Run:
 *   Get-Content ..\tests\P3\01.in | .\P3.exe
 *
 * Solution functions:
 *   comes_before - true when a should leave the heap before b
 *   push         - add an Item and bubble it up
 *   pop          - remove the best Item and sift the last Item down
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

static int comes_before(Item a, Item b) {
    if (a.value != b.value) {
        return a.value > b.value;
    }
    return a.list < b.list;
}

static void swap(Item *a, Item *b) {
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static void push(Item *heap, int *size, Item item) {
    int index = (*size)++;
    heap[index] = item;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!comes_before(heap[index], heap[parent])) {
            break;
        }
        swap(&heap[index], &heap[parent]);
        index = parent;
    }
}

static Item pop(Item *heap, int *size) {
    Item top = heap[0];
    heap[0] = heap[--(*size)];

    int index = 0;
    for (;;) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;

        if (left < *size && comes_before(heap[left], heap[best])) {
            best = left;
        }
        if (right < *size && comes_before(heap[right], heap[best])) {
            best = right;
        }
        if (best == index) {
            break;
        }

        swap(&heap[index], &heap[best]);
        index = best;
    }

    return top;
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

    if (heap_size == 0) {
        printf("EMPTY\n");
        free(heap);
        for (int i = 0; i < k; i++) {
            free(lists[i].data);
        }
        free(lists);
        return 0;
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

    free(heap);
    for (int i = 0; i < k; i++) {
        free(lists[i].data);
    }
    free(lists);
    return 0;
}
