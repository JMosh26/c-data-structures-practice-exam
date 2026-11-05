/*
 * P1 - Min-Heap Machine
 * A binary min-heap driven by INSERT / EXTRACT / PEEK / SIZE / PRINT.
 *
 * Compile: gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 */

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 1005

static int heap[MAX_ITEMS];
static int heap_size = 0;

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void push(int value) {
    int index = heap_size++;
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

static int pop(void) {
    int top = heap[0];
    heap[0] = heap[--heap_size];

    int index = 0;
    for (;;) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap_size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap_size && heap[right] < heap[smallest]) {
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

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) {
        return 0;
    }

    char command[16];

    for (int i = 0; i < q; i++) {
        if (scanf("%15s", command) != 1) {
            break;
        }

        if (strcmp(command, "INSERT") == 0) {
            int value;
            scanf("%d", &value);
            push(value);
        } else if (strcmp(command, "EXTRACT") == 0) {
            if (heap_size == 0) {
                printf("EMPTY\n");
            } else {
                printf("%d\n", pop());
            }
        } else if (strcmp(command, "PEEK") == 0) {
            if (heap_size == 0) {
                printf("EMPTY\n");
            } else {
                printf("%d\n", heap[0]);
            }
        } else if (strcmp(command, "SIZE") == 0) {
            printf("%d\n", heap_size);
        } else if (strcmp(command, "PRINT") == 0) {
            if (heap_size == 0) {
                printf("EMPTY\n");
            } else {
                for (int j = 0; j < heap_size; j++) {
                    printf("%d%s", heap[j], j + 1 == heap_size ? "" : " ");
                }
                printf("\n");
            }
        }
    }

    return 0;
}
