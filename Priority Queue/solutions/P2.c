/*
 * P2 - Air Traffic
 * Answer key: a max-heap with a three-key flight comparator.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Solution functions:
 *   higher_priority - true when a should land before b
 *   push            - add a flight and bubble up
 *   pop             - remove the highest-priority flight and sift down
 *   peek            - read the highest-priority flight
 */

#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 1005

typedef struct {
    char flight[16];
    int emergency;
    int time;
} Flight;

static int higher_priority(const Flight *a, const Flight *b) {
    if (a->emergency != b->emergency) {
        return a->emergency > b->emergency;
    }
    if (a->time != b->time) {
        return a->time < b->time;
    }
    return strcmp(a->flight, b->flight) < 0;
}

static void swap(Flight *a, Flight *b) {
    Flight tmp = *a;
    *a = *b;
    *b = tmp;
}

static void push(Flight *heap, int *size, Flight flight) {
    int index = (*size)++;
    heap[index] = flight;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!higher_priority(&heap[index], &heap[parent])) {
            break;
        }
        swap(&heap[index], &heap[parent]);
        index = parent;
    }
}

static Flight pop(Flight *heap, int *size) {
    Flight top = heap[0];
    heap[0] = heap[--(*size)];

    int index = 0;
    for (;;) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;

        if (left < *size && higher_priority(&heap[left], &heap[best])) {
            best = left;
        }
        if (right < *size && higher_priority(&heap[right], &heap[best])) {
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

static const Flight *peek(const Flight *heap, int size) {
    (void)size;
    return &heap[0];
}

int main(void) {
    Flight heap[MAX_FLIGHTS];
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
            Flight flight;
            scanf("%15s %d %d", flight.flight, &flight.emergency, &flight.time);
            push(heap, &size, flight);
        } else if (strcmp(command, "LAND") == 0) {
            if (size == 0) {
                printf("NONE\n");
            } else {
                Flight flight = pop(heap, &size);
                printf("LANDING %s %d %d\n", flight.flight, flight.emergency, flight.time);
            }
        } else if (strcmp(command, "NEXT") == 0) {
            if (size == 0) {
                printf("NONE\n");
            } else {
                const Flight *flight = peek(heap, size);
                printf("%s %d %d\n", flight->flight, flight->emergency, flight->time);
            }
        } else if (strcmp(command, "COUNT") == 0) {
            printf("%d\n", size);
        }
    }

    return 0;
}
