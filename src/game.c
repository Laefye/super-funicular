#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

game_t* game_new() {
    game_t* game = calloc(1, sizeof(game_t));
    return game;
}

void game_delete(game_t* game) {
    free(game);
}

const char* ascii_arrow(arrow_t* arrow) {
    return arrow->type ? (((arrow->flags & ARROW_DIRECTION_MASK) == ARROW_UP) ? "U" : ((arrow->flags & ARROW_DIRECTION_MASK) == ARROW_RIGHT) ? "R" : ((arrow->flags & ARROW_DIRECTION_MASK) == ARROW_BOTTOM) ? "D" : ((arrow->flags & ARROW_DIRECTION_MASK) == ARROW_LEFT) ? "L" : "") : "";
}

void game_arrow_logic(size_t x, size_t y, arrow_t* arrow, game_t* game) {
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
            if (game->power_map[y][x] && dx + x >= 0 && dx + x < BOARD_SIZE && dy + y >= 0 && dy + y < BOARD_SIZE) {
                game->next_power_map[y + dy][x + dx] += 1;
            }
            break;
        case ARROW_TYPE_OUT:
            if (y < BOARD_SIZE - 1) game->next_power_map[y + 1][x] += 1;
            if (y > 0)              game->next_power_map[y - 1][x] += 1;
            if (x < BOARD_SIZE - 1) game->next_power_map[y][x + 1] += 1;
            if (x > 0)              game->next_power_map[y][x - 1] += 1;
            break;
        default:
            break;
    }
}

void game_tick(game_t* game) {
    for (size_t y = 0; y < BOARD_SIZE; y++) {
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            game->next_power_map[y][x] = 0;
        }
    }
    for (size_t y = 0; y < BOARD_SIZE; y++) {
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            if (game->arrow_map[y][x].type) {
                game_arrow_logic(x, y, game->arrow_map[y] + x, game);
            }
        }
    }
    for (size_t y = 0; y < BOARD_SIZE; y++) {
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            game->power_map[y][x] = game->next_power_map[y][x];
        }
    }
}

void game_print(game_t* game) {
    for (size_t y = 0; y < BOARD_SIZE; y++) {
        for (size_t x = 0; x < BOARD_SIZE; x++) {
            printf("%1s%d|", ascii_arrow(game->arrow_map[y] + x), game->power_map[y][x]);
        }
        printf("\n");
    }
}
