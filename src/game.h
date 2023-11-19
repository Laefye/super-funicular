#ifndef GAME_H
#define GAME_H
#include "arrow.h"
#define BOARD_SIZE 20
#include "api.h"

typedef struct game_t game_t;

struct game_t {
    arrow_t arrow_map[BOARD_SIZE][BOARD_SIZE];
    power_t power_map[BOARD_SIZE][BOARD_SIZE];
    power_t next_power_map[BOARD_SIZE][BOARD_SIZE];
};

// Allocate mememory and init game
API game_t* game_new();

// Free memory and "destroy" game
API void game_delete(game_t* game);

// For debugging, print table in stdout
API void game_print(game_t* game);

// Tick game
API void game_tick(game_t* game);

#endif
