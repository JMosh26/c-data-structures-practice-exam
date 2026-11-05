/*
 * P1 - Min-Heap Machine
 * Answer key: a binary min-heap driven by INSERT / EXTRACT / PEEK / SIZE / PRINT.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Solution functions:
 *   push       - insert a value and bubble it up
 *   pop        - remove the minimum and sift the last value down
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

static void print_heap(const int *heap, int size) {
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

        if (strcmp(command, "INSERT") == 0) {
            int value;
            scanf("%d", &value);
            push(heap, &size, value);
        } else if (strcmp(command, "EXTRACT") == 0) {
            if (size == 0) {
                printf("EMPTY\n");
            } else {
                printf("%d\n", pop(heap, &size));
            }
        } else if (strcmp(command, "PEEK") == 0) {
            if (size == 0) {
                printf("EMPTY\n");
            } else {
                printf("%d\n", heap[0]);
            }
        } else if (strcmp(command, "SIZE") == 0) {
            printf("%d\n", size);
        } else if (strcmp(command, "PRINT") == 0) {
            if (size == 0) {
                printf("EMPTY\n");
            } else {
                print_heap(heap, size);
            }
        }
    }

    return 0;
}
