#include "digits.h"
#include "grid.h"
#include "libft/libft.h"
#include "header.h"
#include "menu.h"
#include <ncurses.h>
#include <stddef.h>

static int	get_correct_color(int num);

void print_score(t_grid *grid)
{
	box(grid->score_win, 0, 0);
	wattron(grid->score_win, A_BOLD);
	mvwprintw(grid->score_win, 1, 2, "Score: %ld", grid->score);
	wattroff(grid->score_win, A_BOLD);
	wrefresh(grid->score_win);
}

void print_scoreboard(t_grid *grid)
{
	box(grid->scoreboard->win, 0, 0);
	wattron(grid->scoreboard->win, A_BOLD);
	mvwprintw(grid->scoreboard->win, 1, (grid->scoreboard->win_width - 10) / 2, "Highscores");
	wattroff(grid->scoreboard->win, A_BOLD);
	int i = 0;
	while (i < grid->scoreboard->amount && i + 4 < grid->scoreboard->win_height)
	{
		mvwprintw(grid->scoreboard->win, i + 3, 1, "%d.", i + 1);
		mvwprintw(grid->scoreboard->win, i + 3, grid->scoreboard->win_width - 1 - ft_nbrlen_base(grid->scoreboard->scores[i].score, 10), "%ld", grid->scoreboard->scores[i].score);
		i++;
	}
	wrefresh(grid->scoreboard->win);
}

static void print_number(t_grid *grid, int nbr, int pos_y, int pos_x)
{
	const int max_digit_amount = grid->size == 4 ? 6 : 8;
	const int digit_amount = ft_nbrlen_base(nbr, 10);

	if (grid->box_width < max_digit_amount * 3) {
		// normal digits
		const int y = pos_y + (grid->box_height / 2);
		const int x = pos_x + ((grid->box_width - digit_amount) / 2);
		mvwprintw(grid->grid_win, y, x, "%d", nbr);
		return;
	}

	// right to left
	for (int d = 0, mag = 1; d < digit_amount; d++) {
		const int digit = nbr / mag % 10;
		mag *= 10;

		const char *ascii_art;
		int digit_height;
		int digit_width;
		int spacing;
		if (grid->box_width < max_digit_amount * 5) {
			ascii_art = THREE_BY_THREE[digit];
			digit_height = 3;
			digit_width = 3;
			spacing = 0;
		}
		else if (grid->box_width < max_digit_amount * (6 + 1 /*spacing*/)) {
			ascii_art = FIVE_BY_FIVE[digit];
			digit_height = 5;
			digit_width = 5;
			spacing = 0;
		}
		else {
			ascii_art = SIX_BY_FIVE[digit];
			digit_height = 5;
			digit_width = 6;
			spacing = 1;
		}

		const int y = pos_y + ((grid->box_height - digit_height) / 2);
		const int x = pos_x + ((grid->box_width - digit_amount * (digit_width + spacing)) / 2);
		const int digit_offset = (digit_amount - d - 1) * (digit_width + spacing);
		for (int i = 0; i < digit_height; i++) {
			mvwprintw(grid->grid_win,
			          y + i,
			          x + digit_offset,
			          "%*.*s",
			          digit_width + spacing,
			          digit_width,
			          ascii_art + (i * digit_width));
		}
	}
}

void print_grid(t_grid *grid)
{
	int i = 0;
	int j;

	clear();
	print_score(grid);
	if (grid->scoreboard->amount > 0)
		print_scoreboard(grid);
	box(grid->grid_win, 0, 0);
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
			wattr_on(grid->grid_win, COLOR_PAIR(get_correct_color(*grid_at(grid, i, j))) | A_BOLD, 0);
			int y = i * grid->box_height + 1;
			int x = j * grid->box_width + 2;
			for(int i = 0; i < grid->box_height; i++)
				mvwprintw(grid->grid_win, y + i, x, "%*c", grid->box_width, ' ');
			if (*grid_at(grid, i, j) != 0)
				print_number(grid, *grid_at(grid, i, j), y, x);
			wattr_off(grid->grid_win, COLOR_PAIR(get_correct_color(*grid_at(grid, i, j))) | A_BOLD, 0);
			j++;
		}
		i++;
	}
	wrefresh(grid->score_win);
	wrefresh(grid->grid_win);
	wrefresh(grid->scoreboard->win);
}

bool display_game_over(t_grid *grid)
{
	switch (popup_menu("GAME OVER", (const char *[]){"Restart", "Quit", NULL}, grid)) {
	case 0:
		print_grid(grid);
		return (true);
	case 1:
		return (false);
	default:
		return (false);
	}
}

bool display_win(t_grid *grid)
{
	switch (popup_menu("You win!", (const char *[]){"Continue", "Quit", NULL}, grid)) {
	case 0:
		print_grid(grid);
		return (true);
	case 1:
		return (false);
	default:
		return (false);
	}
}

static int	get_correct_color(int num)
{
	switch (num) {
	case 0:
		return (COLOR_EMPTY);
	case 2:
		return (COLOR_2);
	case 4:
		return (COLOR_4);
	case 8:
		return (COLOR_8);
	case 16:
		return (COLOR_16);
	case 32:
		return (COLOR_32);
	case 64:
		return (COLOR_64);
	case 128:
		return (COLOR_128);
	case 256:
		return (COLOR_256);
	case 512:
		return (COLOR_512);
	case 1024:
		return (COLOR_1024);
	case 2048:
		return (COLOR_2048);
	case 4096:
		return (COLOR_4096);
	case 8192:
		return (COLOR_8192);
	case 16384:
		return (COLOR_16384);
	case 32768:
		return (COLOR_32768);
	case 65536:
		return (COLOR_65536);
	case 131072:
		return (COLOR_131072);
	default:
		return (COLOR_MAX);
	}
}
