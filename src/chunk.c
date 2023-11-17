#include "chunk.h"
#include <stdlib.h>
#include <stdio.h>

chunk_t* chunk_alloc(chunk_t* previous) {
    chunk_t* current = calloc(1, sizeof(chunk_t));
    if (previous) {
        previous->next = current;
        current->previous = previous;
    }
    return current;
}

void chunk_free(chunk_t* current) {
    if (current->previous) {
        current->previous->next = current->next;
    }
    free(current);
}

void chunk_free_chain(chunk_t* next) {
    while (next->previous) {
        next = next->previous;
    }
    do {
        chunk_t* future_next = next->next;
        chunk_free(next);
        next = future_next;
    } while (next);
}
