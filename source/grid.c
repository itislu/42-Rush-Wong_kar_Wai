#include "grid.h"

int *grid_at(t_grid *grid, int row, int col)
{
	return (&grid->data[row * grid->size + col]);
}
