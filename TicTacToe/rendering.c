#include "rendering.h"
#include <math.h>

const SDL_Color PLAYER_X_COLOR = {.r = 51, .g = 153, .b = 255, .a = 255};
const SDL_Color PLAYER_O_COLOR = { .r = 255, .g = 0, .b = 0, .a = 255 };
const SDL_Color TIE_COLOR = { .r = 112, .g = 128, .b = 144, .a = 255 };
const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .b = 255, .a = 255 };

static void render_draw_circle(SDL_Renderer* renderer, float x, float y, float radius) {
	const int number_of_points = 360;
	for (int i = 0; i < number_of_points; i++) {
		int x_point = cos(i) * radius;
		int y_point = sin(i) * radius;
		SDL_RenderDrawPoint(renderer, x + x_point, y + y_point);
	}
	SDL_RenderDrawPoint(renderer, x + radius, y);
}

void render_grid(SDL_Renderer* renderer, SDL_Color* color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

	for (int i = 1; i < N; i++) {
		SDL_RenderDrawLine(renderer, CELL_WIDTH * i, 0, CELL_WIDTH * i, SCREEN_HEIGHT);
	}
	for (int i = 1; i < N; i++) {
		SDL_RenderDrawLine(renderer, 0, CELL_HEIGHT * i, SCREEN_WIDTH, CELL_HEIGHT * i);
	}
}

void render_x(SDL_Renderer* renderer, int row, int column, const SDL_Color* color) {
	const float half_cell_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float center_x = CELL_WIDTH * 0.5 + row * CELL_HEIGHT;
	const float center_y = CELL_HEIGHT * 0.5 + column * CELL_WIDTH;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	// Draw lines to produce X 
	// Draw first line
	SDL_RenderDrawLine(renderer, 
						center_x - half_cell_side,
						center_y - half_cell_side,
						center_x + half_cell_side,
						center_y + half_cell_side);
	// Draw Second line
	SDL_RenderDrawLine(renderer, 
						center_x + half_cell_side,
						center_y - half_cell_side,
						center_x - half_cell_side,
						center_y + half_cell_side);

}

void render_o(SDL_Renderer* renderer, int row, int column, const SDL_Color* color) {
	const float half_cell_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float center_x = CELL_WIDTH * 0.5 + row * CELL_HEIGHT;
	const float center_y = CELL_HEIGHT * 0.5 + column * CELL_WIDTH;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

	// Draw points to produce circle O
	render_draw_circle(renderer, center_x, center_y, half_cell_side);
}

void render_board(SDL_Renderer* renderer, const int* board, SDL_Color* player_x_color, SDL_Color* player_o_color) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i * N + j] == PLAYER_X) {
				render_x(renderer, j, i, player_x_color);
			}
			else if (board[i * N + j] == PLAYER_O) {
				render_o(renderer, j, i, player_o_color);
			}
		}
	}
}

void render_runnning_state(SDL_Renderer* renderer, game_t* game) {
	render_grid(renderer, &GRID_COLOR);
	render_board(renderer, game->board, &PLAYER_X_COLOR, &PLAYER_O_COLOR);
}

void render_game_over_state(SDL_Renderer* renderer, const game_t* game, const SDL_Color* color) {
	render_grid(renderer, color);
	render_board(renderer, game->board, color, color);
}

void render_game(SDL_Renderer* renderer, const game_t* game) {
	switch (game->state) {
	case RUNNING_STATE:
		render_runnning_state(renderer, game);
		break;

	case PLAYER_X_WON_STATE:
		render_game_over_state(renderer, game, &PLAYER_X_COLOR);
		break;

	case PLAYER_O_WON_STATE:
		render_game_over_state(renderer, game, &PLAYER_O_COLOR);
		break;

	case TIE_STATE:
		render_game_over_state(renderer, game, &TIE_COLOR);
		break;

	case QUIT_STATE:
		break;

	default:
		break;
	}
}