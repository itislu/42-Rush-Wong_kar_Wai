#include "header.h"
#include "grid.h"
#include "libft/libft.h"
#include "menu.h"
#include "scoreboard.h"
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int validate_if_lost(t_grid *grid)
{
	int i = 0;
	int j;
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
			if (*grid_at(grid, i, j) == 0)
				return (1);
			if (i + 1 < grid->size && *grid_at(grid, i, j) == *grid_at(grid, i + 1, j))
				return (1);
			if (j + 1 < grid->size && *grid_at(grid, i, j) == *grid_at(grid, i, j + 1))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

bool is_win_condition(t_grid *grid)
{
	int i = 0;
	int j;
	static bool win = false;

	if (win)
		return (false);
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
			if (*grid_at(grid, i, j) == grid->win_value)
			{
				win = true;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool game_loop(t_grid *grid)
{
	int input;

	while (1)
	{
		if (!continue_if_term_size_ok(grid, grid->min_height + grid->height_extra, grid->min_width + grid->width_extra))
			return (false);
		if (validate_if_lost(grid) == 0)
		{
			if (display_game_over(grid))
				return (true);
			break;
		}

		input = ft_tolower(wgetch(grid->grid_win));
		if (input == KEY_RESIZE)
		{
			continue;
		}
		if (input == 'k' || input == 'w' || input == KEY_UP)
		{
			if (validate_move(grid, KEY_UP) == 0)
				continue;
			move_up(grid);
			up_merge(grid);
			move_up(grid);
		}
		else if (input == 'j' || input == 's' || input == KEY_DOWN)
		{
			if (validate_move(grid, KEY_DOWN) == 0)
				continue;
			move_down(grid);
			down_merge(grid);
			move_down(grid);
		}
		else if (input == 'h' || input == 'a' || input == KEY_LEFT)
		{
			if (validate_move(grid, KEY_LEFT) == 0)
				continue;
			move_left(grid);
			left_merge(grid);
			move_left(grid);
		}
		else if (input == 'l' || input == 'd' || input == KEY_RIGHT)
		{
			if (validate_move(grid, KEY_RIGHT) == 0)
				continue;
			move_right(grid);
			right_merge(grid);
			move_right(grid);
		}
		else if (input == 'q' || input == ESCAPE)
		{
			break;
		}
		else 
		{
			continue;
		}

		if (is_win_condition(grid))
		{
			print_grid(grid);
			if (!display_win(grid))
				return (false);
		}
		else 
		{
			spawn_new_number(grid);
		}
	}
	return (false);
}

void validate_win_value(t_grid *grid)
{
	int result = 2;
	int n = grid->size * grid->size + 1;
	while (n > 0 && WIN_VALUE >= 8)
	{
		if (result == WIN_VALUE)
		{
			grid->win_value = WIN_VALUE;
			return ;
		}
		result *= 2;
		n--;
	}
	grid->win_value = 2048;
}

int main(void)
{
	t_scoreboard scoreboard = {0};
	if (!init_ncurses()) {
		return 0;
	}
	while (1)
	{
		t_grid grid = {.height_extra = 3 /*score*/ + 2 /*frame*/,
		               .width_extra = 4 /*frame*/};
		grid.scoreboard = &scoreboard;

		switch (popup_menu("Choose a grid size", (const char *[]){"4x4", "5x5", NULL}, NULL)) {
		case 0:
			grid.size = 4;
			grid.min_height = 3 * grid.size;
			break;
		case 1:
			grid.size = 5;
			grid.min_height = 5 * grid.size;
			break;
		default:
			goto end;
		}
		if (!read_scorefile(&scoreboard, grid.size)) {
			break;
		}
		if (scoreboard.amount > 0)
		{
			scoreboard.win_width = ft_max(ft_nbrlen_base(scoreboard.scores[0].score, 10) + 5 /*rank*/, 12 /*title*/) + 2 /*frame*/;
			grid.width_extra += 1 /*spacing*/ + scoreboard.win_width;
		}
	
		validate_win_value(&grid);
		int grid_data[grid.size][grid.size];
		grid.data = (int *)grid_data;
		grid.min_width = grid.min_height * 2;
		set_box_size(&grid);

		init_windows(&grid);
		init_grid(&grid);
		bool restart = game_loop(&grid);
		save_score(grid.score, grid.size);
		delwin(grid.grid_win);
		delwin(grid.score_win);
		delwin(grid.scoreboard->win);
		ft_free_and_null((void **)&scoreboard.scores);
		if (restart == false)
			break;
	}
end:
	free(scoreboard.scores);
	endwin();
	return (0);
}
