#ifndef CHUNK_H
#define CHUNK_H
#include "arrow.h"
#define MAX_PER_CHUNK 30


// ██████╗░░█████╗░███╗░░██╗██╗████████╗  ██╗░░░██╗░██████╗███████╗
// ██╔══██╗██╔══██╗████╗░██║╚█║╚══██╔══╝  ██║░░░██║██╔════╝██╔════╝
// ██║░░██║██║░░██║██╔██╗██║░╚╝░░░██║░░░  ██║░░░██║╚█████╗░█████╗░░
// ██║░░██║██║░░██║██║╚████║░░░░░░██║░░░  ██║░░░██║░╚═══██╗██╔══╝░░
// ██████╔╝╚█████╔╝██║░╚███║░░░░░░██║░░░  ╚██████╔╝██████╔╝███████╗
// ╚═════╝░░╚════╝░╚═╝░░╚══╝░░░░░░╚═╝░░░  ░╚═════╝░╚═════╝░╚══════╝
//
// TODO: Как нибудь сделать в будущем

typedef struct chunk_t chunk_t;

struct chunk_t {
    arrow_t data[MAX_PER_CHUNK];
    chunk_t* next;
    chunk_t* previous;
};

// Allocate new chunk and link with previous
// If previous is null, it's mean that it first chunk
chunk_t* chunk_alloc(chunk_t* previous);

// Free chunk and combine previous and next
void chunk_free(chunk_t* current);

// Free all chunks (from real begin)
void chunk_free_chain(chunk_t* first);

#endif
