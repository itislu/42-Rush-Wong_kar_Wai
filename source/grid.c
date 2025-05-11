#include "grid.h"
#include "header.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void init_grid(t_grid *grid)
{
	ft_memset(grid->data, 0, sizeof(int) * grid->size * grid->size);
	srand(time(NULL));
	// *grid_at(grid, 0, 0) = 512;
	// *grid_at(grid, 0, 1) = 1024;
	// *grid_at(grid, 0, 2) = 2048;
	// *grid_at(grid, 0, 3) = 4096;
	// *grid_at(grid, 1, 0) = 8192;
	// *grid_at(grid, 1, 1) = 16384;
	// *grid_at(grid, 1, 2) = 32768;
	// *grid_at(grid, 1, 3) = 65536;
	// *grid_at(grid, 2, 0) = 131072;
	// *grid_at(grid, 2, 1) = 262144;
	spawn_new_number(grid);
	spawn_new_number(grid);
}

int *grid_at(t_grid *grid, int row, int col)
{
	return (&grid->data[row * grid->size + col]);
}

void spawn_new_number(t_grid *grid)
{
	int i;
	int j;
	while (1)
	{
		i = rand() % grid->size;
		j = rand() % grid->size;
		if (*grid_at(grid, i, j) == 0)
		{
			if (rand() % 10 < 9)
				*grid_at(grid, i, j) = 2;
			else
				*grid_at(grid, i, j) = 4;
			break;
		}
	}
}
