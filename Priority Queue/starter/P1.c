/*
 * P1 - Roller Coaster
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
 *   peek       - read the minimum
 *   take_k     - remove and print the k smallest values
 *   print_heap - print the internal array in level order
 */

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 1005

static void swap(int *a, int *b) {
    /* TODO: exchange *a and *b */
    (void)a;
    (void)b;
}

static void push(int *heap, int *size, int value) {
    /* TODO: append the value and bubble it up */
    (void)heap;
    (void)size;
    (void)value;
}

static int pop(int *heap, int *size) {
    /* TODO: save the root, move the last value to the root, sift down,
       and return the saved minimum */
    (void)heap;
    (void)size;
    return 0;
}

static int peek(const int *heap, int size) {
    /* TODO: return the root */
    (void)size;
    return heap[0];
}

static int take_k(int *heap, int *size, int k) {
    /* TODO: pop and print min(k, size) values on one line, or EMPTY */
    (void)heap;
    (void)size;
    (void)k;
    return 0;
}

static void print_heap(const int *heap, int size) {
    /* TODO: print the heap array in level order, or EMPTY */
    (void)heap;
    (void)size;
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
