#include "logic.h"
#include "game.h"
#include <stdbool.h>
#include <stdio.h>

void click_cell(game_t* game, int row, int column) {
	if (game->state == RUNNING_STATE) {
		player_turn(game, row, column);
	}
	else {
		reset_game(game);
	}
}

void player_turn(game_t* game, int row, int column) {
	// If cell is empty fill with X or O
	if (game->board[row * N + column] == EMPTY) {
		game->board[row * N + column] = game->player;
		// Switch player
		if (game->player == PLAYER_X) {
			game->player = PLAYER_O;
		}
		else {
			game->player = PLAYER_X;
		}
		// Check game over condition
		game_over_condition(game);
	}
}

void reset_game(game_t* game) {
	game->player = PLAYER_X;
	game->state = RUNNING_STATE;
	// Reset board
	for (int i = 0; i < N * N; i++) {
		game->board[i] = EMPTY;
	}
}

bool check_player_won(game_t* game, int player) {
	int row_count = 0;
	int column_count = 0;
	int diagonal_count_back = 0;	
	int diagonal_count_front = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (game->board[i * N + j] == player) {
				row_count++;
			}
			if (game->board[j * N + i] == player) {
				column_count++;
			}
		}

		if (row_count >= N || column_count >= N) {
			return true;
		}

		row_count = 0;
		column_count = 0;

		if (game->board[i * N + i] == player) {
			diagonal_count_back++;
		}
		if (game->board[i * N + (N - i - 1)] == player) {
			diagonal_count_front++;
		}
	}
	if (diagonal_count_back >= N || diagonal_count_front >= N) {
		return true;
	}
	return false;
}

int count_cells(const int* board, int cell) {
	int count = 0;
	for (int i = 0; i < N * N; i++) {
		if (board[i] == cell) {
			count++;
		}
	}
	return count;
}

void game_over_condition(game_t* game) {
	if (check_player_won(game, PLAYER_X)) {
		game->state = PLAYER_X_WON_STATE;
	}
	else if (check_player_won(game, PLAYER_O)) {
		game->state = PLAYER_O_WON_STATE;
	}
	else if (count_cells(game->board, EMPTY) == 0) {
		game->state = TIE_STATE;
	}
}