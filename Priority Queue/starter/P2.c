/*
 * P2 - ER Triage
 * Read the full statement in ..\problems\P2.md.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Starter functions:
 *   push - add a patient and bubble up
 *   pop  - remove the highest-priority patient and sift down
 *
 * Suggested helper (write it yourself):
 *   higher_priority(a, b) - true when a should be treated before b.
 *   Compare severity first, then the smaller arrival number.
 */

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 1005

typedef struct {
    char name[32];
    int severity;
    int arrival;
} Patient;

static void push(Patient *heap, int *size, Patient patient) {
    /* TODO: append at heap[*size], increment *size, then bubble up */
    (void)heap;
    (void)size;
    (void)patient;
}

static Patient pop(Patient *heap, int *size) {
    /* TODO: save the root, move the last patient to the root, decrement *size,
       then sift down using severity and arrival order */
    (void)heap;
    (void)size;
    Patient empty = {"", 0, 0};
    return empty;
}

int main(void) {
    Patient heap[MAX_PATIENTS];
    int size = 0;
    int next_arrival = 0;

    int q;
    if (scanf("%d", &q) != 1) {
        return 0;
    }

    char command[16];

    for (int i = 0; i < q; i++) {
        if (scanf("%15s", command) != 1) {
            break;
        }

        if (strcmp(command, "ARRIVE") == 0) {
            Patient patient;
            scanf("%31s %d", patient.name, &patient.severity);
            patient.arrival = next_arrival++;
            push(heap, &size, patient);
        } else if (strcmp(command, "TREAT") == 0) {
            if (size == 0) {
                printf("NO PATIENTS\n");
            } else {
                Patient patient = pop(heap, &size);
                printf("TREATING %s %d\n", patient.name, patient.severity);
            }
        } else if (strcmp(command, "NEXT") == 0) {
            if (size == 0) {
                printf("NO PATIENTS\n");
            } else {
                printf("%s %d\n", heap[0].name, heap[0].severity);
            }
        } else if (strcmp(command, "COUNT") == 0) {
            printf("%d\n", size);
        }
    }

    return 0;
}
