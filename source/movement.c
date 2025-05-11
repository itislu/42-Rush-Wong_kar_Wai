
#include "grid.h"
#include "libft/libft.h"
#include <ncurses.h>

int left_merge(t_grid *grid)
{
	int i = 0;
	int j;
	int merged = 0;
	while (i < grid->size)
	{
		j = 0;
		while (j + 1 < grid->size)
		{
			if (*grid_at(grid, i, j) != 0 && *grid_at(grid, i, j) == *grid_at(grid, i, j + 1))
			{
				*grid_at(grid, i, j) = *grid_at(grid, i, j) + *grid_at(grid, i, j + 1);
				*grid_at(grid, i, j + 1) = 0;
				grid->score += *grid_at(grid, i, j);
				merged = 1;
			}
			j++;
		}
		i++;
	}
	return (merged);
}

int move_left(t_grid *grid)
{
	int i = 0;
	int j;
	int l;
	int moved = 0;
	while (i < grid->size)
	{
		j = 1;
		while (j < grid->size)
		{
			if (*grid_at(grid, i, j) != 0)
			{
				l = j;
				while (l > 0 && *grid_at(grid, i, l - 1) == 0)
				{
					*grid_at(grid, i, l - 1) = *grid_at(grid, i, l);
					*grid_at(grid, i, l) = 0;
					l--;
					moved = 1;
				}
			}
			j++;
		}
		i++;
	}
	return (moved);
}

int right_merge(t_grid *grid)
{
	int i = 0;
	int j;
	int merged = 0;
	while (i < grid->size)
	{
		j = grid->size - 1;
		while (j - 1 >= 0)
		{
			if (*grid_at(grid, i, j) != 0 && *grid_at(grid, i, j) == *grid_at(grid, i, j - 1))
			{
				*grid_at(grid, i, j) = *grid_at(grid, i, j) + *grid_at(grid, i, j - 1);
				*grid_at(grid, i, j - 1) = 0;
				grid->score += *grid_at(grid, i, j);
				merged = 1;
			}
			j--;
		}
		i++;
	}
	return (merged);
}

int move_right(t_grid *grid)
{
	int i = 0;
	int j;
	int l;
	int moved = 0;
	while (i < grid->size)
	{
		j = grid->size - 2;
		while (j >= 0)
		{
			if (*grid_at(grid, i, j) != 0)
			{
				l = j;
				while (l < grid->size - 1 && *grid_at(grid, i, l + 1) == 0)
				{
					*grid_at(grid, i, l + 1) = *grid_at(grid, i, l);
					*grid_at(grid, i, l) = 0;
					l++;
					moved = 1;
				}
			}
			j--;
		}
		i++;
	}
	return (moved);
}

int up_merge(t_grid *grid)
{
	int j = 0;
	int i;
	int merged = 0;
	while (j < grid->size)
	{
		i = 0;
		while (i + 1 < grid->size)
		{
			if (*grid_at(grid, i, j) != 0 && *grid_at(grid, i, j) == *grid_at(grid, i + 1, j))
			{
				*grid_at(grid, i, j) = *grid_at(grid, i, j) + *grid_at(grid, i + 1, j);
				*grid_at(grid, i + 1, j) = 0;
				grid->score += *grid_at(grid, i, j);
				merged = 1;
			}
			i++;
		}
		j++;
	}
	return (merged);
}

int move_up(t_grid *grid)
{
	int j = 0;
	int i;
	int l;
	int moved = 0;
	while (j < grid->size)
	{
		i = 1;
		while (i < grid->size)
		{
			if (*grid_at(grid, i, j) != 0)
			{
				l = i;
				while (l > 0 && *grid_at(grid, l - 1, j) == 0)
				{
					*grid_at(grid, l - 1, j) = *grid_at(grid, l, j);
					*grid_at(grid, l, j) = 0;
					l--;
					moved = 1;
				}
			}
			i++;
		}
		j++;
	}
	return (moved);
}

int down_merge(t_grid *grid)
{
	int j = 0;
	int i;
	int merged = 0;
	while (j < grid->size)
	{
		i = grid->size - 1;
		while (i - 1 >= 0)
		{
			if (*grid_at(grid, i, j) != 0 && *grid_at(grid, i, j) == *grid_at(grid, i - 1, j))
			{
				*grid_at(grid, i, j) = *grid_at(grid, i, j) + *grid_at(grid, i - 1, j);
				*grid_at(grid, i - 1, j) = 0;
				grid->score += *grid_at(grid, i, j);
				merged = 1;
			}
			i--;
		}
		j++;
	}
	return (merged);
}

int move_down(t_grid *grid)
{
	int j = 0;
	int i;
	int l;
	int moved = 0;
	while (j < grid->size)
	{
		i = grid->size - 2;
		while (i >= 0)
		{
			if (*grid_at(grid, i, j) != 0)
			{
				l = i;
				while (l < grid->size - 1 && *grid_at(grid, l + 1, j) == 0)
				{
					*grid_at(grid, l + 1, j) = *grid_at(grid, l, j);
					*grid_at(grid, l, j) = 0;
					l++;
					moved = 1;
				}
			}
			i--;
		}
		j++;
	}
	return (moved);
}

int validate_move(t_grid *grid, int input)
{
	int tmp_grid_data[grid->size][grid->size];
	t_grid tmp_grid = {.data = (int *)tmp_grid_data, .size = grid->size};
	ft_memcpy(tmp_grid.data, grid->data, grid->size * grid->size * sizeof(*grid->data));

	if (input == KEY_UP)
	{
		if (move_up(&tmp_grid) == 1)
			return (1);
		if (up_merge(&tmp_grid) == 1)
			return (1);
		if (move_up(&tmp_grid) == 1)
			return (1);
	}
	else if (input == KEY_DOWN)
	{
		if (move_down(&tmp_grid) == 1)
			return (1);
		if (down_merge(&tmp_grid) == 1)
			return (1);
		if (move_down(&tmp_grid) == 1)
			return (1);
	}
	else if (input == KEY_LEFT)
	{
		if (move_left(&tmp_grid) == 1)
			return (1);
		if (left_merge(&tmp_grid) == 1)
			return (1);
		if (move_left(&tmp_grid) == 1)
			return (1);
	}
	else if (input == KEY_RIGHT)
	{
		if (move_right(&tmp_grid) == 1)
			return (1);
		if (right_merge(&tmp_grid) == 1)
			return (1);
		if (move_right(&tmp_grid) == 1)
			return (1);
	}
	return (0);
}
