#ifndef GAME_H
#define GAME_H
#include "arrow.h"
#include "map.h"
#define BOARD_SIZE 20
#include "api.h"

typedef struct game_t game_t;

struct game_t {
    map_t arrow_map;
    map_t power_map;
    map_t next_power_map;
};

API game_t* game_new();

API void game_free(game_t* game);

API void game_tick(game_t* game);

API void game_set_arrow(game_t* game, coordinate_t x, coordinate_t y, arrow_t arrow);

API arrow_t* game_get_arrow(game_t* game, coordinate_t x, coordinate_t y);

API power_t game_get_power(game_t* game, coordinate_t x, coordinate_t y);

#endif
