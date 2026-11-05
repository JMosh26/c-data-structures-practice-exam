/*
 * P1 - Min-Heap Machine
 * Read the full statement in ..\problems\P1.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P1 P1.c
 * Run:
 *   Get-Content ..\tests\P1\01.in | .\P1.exe
 *
 * Starter functions:
 *   push       - insert a value and bubble it up
 *   pop        - remove the minimum and sift the last value down
 *   print_heap - print the internal array in level order
 *
 * You may add a swap() helper if you want one.
 */

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 1005

static void push(int *heap, int *size, int value) {
    /* TODO: append value at heap[*size], increment *size, then bubble up */
    (void)heap;
    (void)size;
    (void)value;
}

static int pop(int *heap, int *size) {
    /* TODO: save heap[0], move the last element to the root, decrement *size,
       then sift down by swapping with the smaller child */
    (void)heap;
    (void)size;
    return 0;
}

static void print_heap(const int *heap, int size) {
    /* TODO: print heap[0..size-1] separated by single spaces */
    (void)heap;
    (void)size;
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
