/*
 * P3 - Merge the Streams
 * Merge K sorted lists with a min-heap of list heads.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P3 P3.c
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

static Item *heap = NULL;
static int heap_size = 0;

static int comes_before(Item a, Item b) {
    return a.value < b.value;
}

static void swap(Item *a, Item *b) {
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static void push(Item item) {
    int index = heap_size++;
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

static Item pop(void) {
    Item top = heap[0];
    heap[0] = heap[--heap_size];

    int index = 0;
    for (;;) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;

        if (left < heap_size && comes_before(heap[left], heap[best])) {
            best = left;
        }
        if (right < heap_size && comes_before(heap[right], heap[best])) {
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

    heap = (Item *)malloc((size_t)(total > 0 ? total : 1) * sizeof(Item));
    if (heap == NULL) {
        return 1;
    }

    for (int i = 0; i < k; i++) {
        if (lists[i].length > 0) {
            Item item;
            item.value = lists[i].data[0];
            item.list = i;
            item.index = 0;
            push(item);
        }
    }

    int first = 1;
    while (heap_size > 0) {
        Item item = pop();
        if (!first) {
            putchar(' ');
        }
        printf("%d", item.value);
        first = 0;

        int next_index = item.index + 1;
        if (next_index < lists[item.list].length) {
            Item next;
            next.value = lists[item.list].data[next_index];
            next.list = item.list;
            next.index = next_index;
            push(next);
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
