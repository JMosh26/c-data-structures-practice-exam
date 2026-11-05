/*
 * P2 - ER Triage
 * Answer key: a max-heap of patients with a severity/arrival comparator.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o P2 P2.c
 * Run:
 *   Get-Content ..\tests\P2\01.in | .\P2.exe
 *
 * Solution functions:
 *   higher_priority - true when a should be treated before b
 *   push            - add a patient and bubble up
 *   pop             - remove the highest-priority patient and sift down
 */

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 1005

typedef struct {
    char name[32];
    int severity;
    int arrival;
} Patient;

static int higher_priority(const Patient *a, const Patient *b) {
    if (a->severity != b->severity) {
        return a->severity > b->severity;
    }
    return a->arrival < b->arrival;
}

static void swap(Patient *a, Patient *b) {
    Patient tmp = *a;
    *a = *b;
    *b = tmp;
}

static void push(Patient *heap, int *size, Patient patient) {
    int index = (*size)++;
    heap[index] = patient;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!higher_priority(&heap[index], &heap[parent])) {
            break;
        }
        swap(&heap[index], &heap[parent]);
        index = parent;
    }
}

static Patient pop(Patient *heap, int *size) {
    Patient top = heap[0];
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
