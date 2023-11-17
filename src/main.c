#include <stdio.h>
#include "game.h"

int main() {
    game_t* game = game_new();
    game->arrow_map[4][6] = MAKE_ARROW(0, 0, ARROW_TYPE_BASIC, ARROW_RIGHT);
    game->arrow_map[4][5] = MAKE_ARROW(0, 0, ARROW_TYPE_BASIC, ARROW_RIGHT);
    game->arrow_map[5][5] = MAKE_ARROW(0, 0, ARROW_TYPE_BASIC, ARROW_UP);
    game->arrow_map[6][5] = MAKE_ARROW(0, 0, ARROW_TYPE_OUT, ARROW_UP);
    for (int i = 0; i < 5; i++) {
        game_tick(game);
        game_print(game);
        printf("\n\n");
    }
    game_delete(game);
}