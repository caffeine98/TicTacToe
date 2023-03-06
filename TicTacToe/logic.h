#ifndef LOGIC_H__
#define LOGIC_H__

#include "game.h"

void click_cell(game_t* game, int row, int column);
void player_turn(game_t* game, int row, int column);
void reset_game(game_t* game);
void game_over_condition(game_t* game);

#endif