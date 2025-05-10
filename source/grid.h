#ifndef GRID_H
#define GRID_H

typedef struct s_grid
{
	int *data;
	int size;
	int box_height;
	int box_width;
} t_grid;

int *grid_at(t_grid *grid, int row, int col);

#endif
