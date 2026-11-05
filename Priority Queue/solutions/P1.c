/*
 * P1 - Roller Coaster
 * Answer key: a binary min-heap with batch extraction.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
 *   push       - insert a value and bubble it up
 *   pop        - remove the minimum and sift the last value down
 *   peek       - read the minimum
 *   take_k     - remove and print the k smallest values
 *   print_heap - print the internal array in level order
 */

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 1005

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void push(int *heap, int *size, int value) {
    int index = (*size)++;
    heap[index] = value;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] <= heap[index]) {
            break;
        }
        swap(&heap[parent], &heap[index]);
        index = parent;
    }
}

static int pop(int *heap, int *size) {
    int top = heap[0];
    heap[0] = heap[--(*size)];

    int index = 0;
    for (;;) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < *size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < *size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }

        swap(&heap[index], &heap[smallest]);
        index = smallest;
    }

    return top;
}

static int peek(const int *heap, int size) {
    (void)size;
    return heap[0];
}

static int take_k(int *heap, int *size, int k) {
    if (*size == 0 || k <= 0) {
        printf("EMPTY\n");
        return 0;
    }

    if (k > *size) {
        k = *size;
    }

    for (int i = 0; i < k; i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", pop(heap, size));
    }
    putchar('\n');

    return k;
}

static void print_heap(const int *heap, int size) {
    if (size == 0) {
        printf("EMPTY\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("%d%s", heap[i], i + 1 == size ? "" : " ");
    }
    putchar('\n');
}

int main(void) {
    int heap[MAX_ITEMS];
    int size = 0;

    int q;
    if (scanf("%d", &q) != 1) {
        return 0;
    }

    char command[16];

    for (int i = 0; i < q; i++) {
        if (scanf("%15s", command) != 1) {
            break;
        }

        if (strcmp(command, "ADD") == 0) {
            int value;
            scanf("%d", &value);
            push(heap, &size, value);
        } else if (strcmp(command, "RIDE") == 0) {
            if (size == 0) {
                printf("EMPTY\n");
            } else {
                printf("RIDE %d\n", pop(heap, &size));
            }
        } else if (strcmp(command, "TAKE") == 0) {
            int k;
            scanf("%d", &k);
            take_k(heap, &size, k);
        } else if (strcmp(command, "PEEK") == 0) {
            if (size == 0) {
                printf("EMPTY\n");
            } else {
                printf("%d\n", peek(heap, size));
            }
        } else if (strcmp(command, "SIZE") == 0) {
            printf("%d\n", size);
        } else if (strcmp(command, "DUMP") == 0) {
            print_heap(heap, size);
        }
    }

    return 0;
}
