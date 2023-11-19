#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

game_t* game_new() {
    game_t* game = calloc(1, sizeof(game_t));
    game->arrow_map = map_new();
    game->power_map = map_new();
    game->next_power_map = map_new();
    return game;
}

void game_free(game_t* game) {
    map_free(game->arrow_map);
    map_free(game->power_map);
    map_free(game->next_power_map);
    free(game);
}

void game_arrow_logic(coordinate_t x, coordinate_t y, arrow_t* arrow, game_t* game) {
    size_t dx = 0;
    size_t dy = 0;
    switch (arrow->flags & ARROW_DIRECTION_MASK) {
        case ARROW_UP:
            dy = -1;
            break;
        case ARROW_RIGHT:
            dx = 1;
            break;
        case ARROW_BOTTOM:
            dy = 1;
            break;
        case ARROW_LEFT:
            dx = -1;
            break;
        default:
            break;
    }
    switch (arrow->type) {
        case ARROW_TYPE_BASIC:
            if (((power_t*) map_get(game->power_map, x, y, 0))[0] > 0) {
                uint8_t is_new = 0;
                ((power_t*) map_get(game->next_power_map, x + dx, y + dy, &is_new))[0] += 1;
                printf("is new %d\n", is_new);
            }
            printf("%d\n", ((power_t*) map_get(game->next_power_map, x, y, 0))[0]);
            break;
        case ARROW_TYPE_OUT:
            ((power_t*) map_get(game->next_power_map, x, y, 0))[0] += 1;
            ((power_t*) map_get(game->next_power_map, x + 1, y, 0))[0] += 1;
            ((power_t*) map_get(game->next_power_map, x - 1, y, 0))[0] += 1;
            ((power_t*) map_get(game->next_power_map, x, y + 1, 0))[0] += 1;
            ((power_t*) map_get(game->next_power_map, x, y - 1, 0))[0] += 1;
            break;
        // case ARROW_TYPE_AND:
        //     if (((power_t*) map_get(game->power_map, x, y, 0))[0] > 1) {
        //         ((power_t*) map_get(game->next_power_map, x, y, 0))[0] += 1;
        //     }
        //     break;
        default:
            break;
    }
}

void game_tick(game_t* game) {
    map_clear(game->next_power_map);
    map_iterator_t* iterator = map_new_iterator(game->arrow_map);
    entry_t* entry;
    while ((entry = map_iterator_next(iterator))) {
        game_arrow_logic(entry->x, entry->y, (arrow_t*) entry->data, game);
    }
    map_free_iterator(iterator);
    map_copy(game->power_map, game->next_power_map);
}

void game_set_arrow(game_t* game, coordinate_t x, coordinate_t y, arrow_t arrow) {
    arrow_t* arrow_from_map = (arrow_t*) map_get(game->arrow_map, x, y, 0);
    memcpy(arrow_from_map, &arrow, sizeof(arrow_t));
}

arrow_t* game_get_arrow(game_t* game, coordinate_t x, coordinate_t y) {
    uint8_t is_new = 0;
    arrow_t* arrow = (arrow_t*) map_get(game->arrow_map, x, y, &is_new);
    if (is_new) {
        arrow->type = 0;
        arrow->flags = 0;
    }
    return arrow;
}

power_t game_get_power(game_t* game, coordinate_t x, coordinate_t y) {
    return ((power_t*) map_get(game->power_map, x, y, 0))[0];
}
