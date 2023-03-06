#ifndef RENDERING_H__
#define RENDERING_H__

#include "game.h"
#include <SDL.h>

static void render_draw_circle(SDL_Renderer* renderer, float x, float y, float radius);

void render_grid(SDL_Renderer* renderer, SDL_Color* color);
void render_x(SDL_Renderer* renderer, int row, int column, const SDL_Color* color);
void render_o(SDL_Renderer* renderer, int row, int column, const SDL_Color* color);
void render_board(SDL_Renderer* renderer, const int* board, SDL_Color* player_x_color, SDL_Color* player_o_color);
void render_runnning_state(SDL_Renderer* renderer, game_t* game);
void render_game_over_state(SDL_Renderer* renderer, const game_t* game, const SDL_Color* color);
void render_game(SDL_Renderer* renderer, const game_t* game);

#endif