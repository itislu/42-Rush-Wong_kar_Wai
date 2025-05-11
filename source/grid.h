#ifndef GRID_H
#define GRID_H

#include <ncurses.h>

typedef struct s_grid
{
	int *data;
	int size;
	int box_height;
	int box_width;
	int score;
	WINDOW *grid_win;
	WINDOW *score_win;
	// int win_value;
} t_grid;

int *grid_at(t_grid *grid, int row, int col);

#endif
