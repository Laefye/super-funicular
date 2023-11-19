#ifndef MAP_H
#define MAP_H
#define MAX_PER_CHUNK 30
#define DATA_SIZE 32
#define ENTRY_FLAG_USED 1
#include <stdint.h>
#include "api.h"

typedef struct entry_t entry_t;
typedef size_t coordinate_t;

struct entry_t {
    uint8_t flags;
    coordinate_t x;
    coordinate_t y;
    uint8_t data[DATA_SIZE];
};

typedef struct chunk_t chunk_t;

struct chunk_t {
    entry_t entries[MAX_PER_CHUNK];
    chunk_t* next;
    chunk_t* previous;
};

chunk_t* chunk_alloc(chunk_t* previous);

API void chunk_free(chunk_t* current);

API void chunk_free_next(chunk_t* first);

typedef chunk_t* map_t;

API map_t map_new();

API void map_free(map_t map);

API uint8_t* map_get(map_t map, coordinate_t x, coordinate_t y, uint8_t* is_new);

API void map_clear(map_t map);

typedef struct map_iterator_t map_iterator_t;

struct map_iterator_t {
    chunk_t* chunk;
    coordinate_t index;
};

API map_iterator_t* map_new_iterator(map_t map);

API void map_free_iterator(map_iterator_t* iterator);

API entry_t* map_iterator_next(map_iterator_t* iterator);

API void chunk_copy(chunk_t* dst, chunk_t* src);

API void map_copy(map_t dst, map_t src);

#endif
