#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

chunk_t* chunk_alloc(chunk_t* previous) {
    chunk_t* current = calloc(1, sizeof(chunk_t));
    if (previous) {
        previous->next = current;
        current->previous = previous;
    }
    return current;
}

void chunk_free(chunk_t* current) {
    if (current->previous && current->next) {
        current->previous->next = current->next;
        current->next->previous = current->previous;
    } else if (current->next) {
        current->next->previous = 0;
    } else if (current->previous) {
        current->previous->next = 0;
    }
    free(current);
}

void chunk_free_next(chunk_t* next) {
    while (next) {
        chunk_t* future_next = next->next;
        chunk_free(next);
        next = future_next;
    }
}

map_t map_new() {
    return (map_t) chunk_alloc(0);
}

void map_free(map_t map) {
    chunk_free_next(map);
}

uint8_t* map_get(map_t map, coordinate_t x, coordinate_t y, uint8_t* is_new) {
    chunk_t* chunk = (chunk_t*) map;
    while (chunk) {
        for (coordinate_t i = 0; i < MAX_PER_CHUNK; i++) {
            if (chunk->entries[i].flags == ENTRY_FLAG_USED) {
                if (chunk->entries[i].x == x && chunk->entries[i].y == y) {
                    if (is_new) *is_new = 0;
                    return chunk->entries[i].data;
                }
            } else {
                if (i + 1 < MAX_PER_CHUNK) {
                    chunk->entries[i].flags = 0;
                } else if (chunk->next) {
                    chunk_free_next(chunk->next);
                }
                if (is_new) *is_new = 1;
                chunk->entries[i].flags = ENTRY_FLAG_USED;
                chunk->entries[i].x = x;
                chunk->entries[i].y = y;
                memset(chunk->entries[i].data, 0, sizeof(uint8_t) * DATA_SIZE);
                return chunk->entries[i].data;
            }
        }
        if (chunk->next) {
            chunk = chunk->next;
        } else {
            chunk = chunk_alloc(chunk);
        }
    }
    return 0;
}

void map_clear(map_t map) {
    map->entries[0].flags = 0;
    chunk_free_next(map->next);
}

map_iterator_t* map_new_iterator(map_t map) {
    map_iterator_t* iterator = calloc(1, sizeof(map_iterator_t));
    iterator->chunk = (chunk_t*) map;
    iterator->index = 0;
    return iterator;
}

void map_free_iterator(map_iterator_t* iterator) {
    free(iterator);
}

entry_t* map_iterator_next(map_iterator_t* iterator) {
    if (iterator->index > MAX_PER_CHUNK - 1 && iterator->chunk) {
        iterator->chunk = iterator->chunk->next;
        iterator->index = 0;
    }
    if (!iterator->chunk) {
        return 0;
    }
    if (iterator->index > MAX_PER_CHUNK - 1) {
        return 0;
    }
    entry_t* value = iterator->chunk->entries + iterator->index;
    if (value->flags != ENTRY_FLAG_USED) {
        return 0;
    }
    iterator->index++;
    return value;
}

void chunk_copy(chunk_t* dst, chunk_t* src) {
    for (coordinate_t i = 0; i < MAX_PER_CHUNK; i++) {
        if (src->entries[i].flags != ENTRY_FLAG_USED) {
            dst->entries[i].flags = 0;
            if (dst->next) {
                chunk_free_next(dst->next);
            }
            break;
        }
        dst->entries[i].x = src->entries[i].x;
        dst->entries[i].y = src->entries[i].y;
        memcpy(dst->entries[i].data, src->entries[i].data, sizeof(uint8_t) * DATA_SIZE);
    }
}

void map_copy(map_t dst, map_t src) {
    chunk_t* src_chunk = (chunk_t*) src;
    chunk_t* dst_chunk = (chunk_t*) dst;
    chunk_t* last_dst_chunk = (chunk_t*) dst;
    while (src_chunk) {
        if (!dst_chunk) {
            dst_chunk = chunk_alloc(last_dst_chunk);
        }
        chunk_copy(dst_chunk, src_chunk);
        src_chunk = src_chunk->next;
        last_dst_chunk = dst_chunk;
    }
}
