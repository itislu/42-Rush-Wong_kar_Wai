#ifndef GRID_H
#define GRID_H

#include "scoreboard.h"
#include <ncurses.h>

typedef struct s_grid
{
	int *data;
	int size;
	int box_height;
	int box_width;
	long score;
	WINDOW *grid_win;
	int grid_win_pos_x;
	int grid_win_pos_y;
	int grid_win_width;
	int grid_win_height;
	WINDOW *score_win;
	int score_win_pos_x;
	int score_win_pos_y;
	int score_win_width;
	int score_win_height;
	int min_height;
	int min_width;
	int height_extra;
	int width_extra;
	int win_value;
	t_scoreboard *scoreboard;
} t_grid;

void init_grid(t_grid *grid);
int *grid_at(t_grid *grid, int row, int col);
void spawn_new_number(t_grid *grid);

#endif
