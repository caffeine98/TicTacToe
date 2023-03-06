#include "game.h"
#include "logic.h"
#include "rendering.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window) {
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	// Create game object
	game_t game = {
		.board = {PLAYER_X, PLAYER_O, PLAYER_O,
				  PLAYER_O, PLAYER_X, EMPTY,
				  EMPTY, EMPTY, PLAYER_X},
		.player = PLAYER_X,
		.state = TIE_STATE
	};

	SDL_Event e;
	while (game.state != QUIT_STATE) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				game.state = QUIT_STATE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				click_cell(&game, e.button.y / CELL_HEIGHT, e.button.x / CELL_WIDTH);
				break;

			default:
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		render_game(renderer, &game);
		
		SDL_RenderPresent(renderer);

		SDL_Delay(1/30);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}