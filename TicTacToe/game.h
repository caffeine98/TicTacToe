#ifndef GAME_H__
#define GAME_H__

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define N 3

#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)

enum GameStates{
	RUNNING_STATE,
	PLAYER_X_WON_STATE,
	PLAYER_O_WON_STATE,
	TIE_STATE,
	QUIT_STATE
};

enum Player {
	EMPTY,
	PLAYER_X,
	PLAYER_O
};

typedef struct {
	int board[N * N];
	int player;
	int state;
} game_t;

#endif // GAME_H__