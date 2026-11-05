/*
 * P2 - Air Traffic
 * Read the full statement in ..\problems\P2.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Starter functions:
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
    /* TODO: higher emergency first; then earlier time; then smaller name */
    (void)a;
    (void)b;
    return 0;
}

static void swap(Flight *a, Flight *b) {
    /* TODO: exchange *a and *b */
    (void)a;
    (void)b;
}

static void push(Flight *heap, int *size, Flight flight) {
    /* TODO: append the flight and bubble it up */
    (void)heap;
    (void)size;
    (void)flight;
}

static Flight pop(Flight *heap, int *size) {
    /* TODO: save the root, move the last flight to the root, sift down,
       and return the saved flight */
    (void)heap;
    (void)size;
    Flight empty = {"", 0, 0};
    return empty;
}

static const Flight *peek(const Flight *heap, int size) {
    /* TODO: return the root */
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
