#include "digits.h"
#include "header.h"
#include "grid.h"
#include "libft/libft.h"
#include "menu.h"
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int sig = 0;

int	get_correct_color(int num)
{
	switch (num) {
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
		return (COLOR_EMPTY);
	}
}

void print_score(t_grid *grid, int center_width)
{
	mvwin(grid->score_win, 0, center_width);
	box(grid->score_win, 0, 0);
	mvwprintw(grid->score_win, 1, 1, "Score: %d", grid->score);
	wrefresh(grid->score_win);
}

void print_number(t_grid *grid, int nbr, int pos_y, int pos_x)
{
	const int digit_amount = ft_nbrlen_base(nbr, 10);

	if (grid->box_width < 18) {
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
		if (grid->box_width < 30) {
			ascii_art = THREE_BY_THREE[digit];
			digit_height = 3;
			digit_width = 3;
		}
		else if (grid->box_width < 36) {
			ascii_art = FIVE_BY_FIVE[digit];
			digit_height = 5;
			digit_width = 5;
		}
		else {
			ascii_art = SIX_BY_FIVE[digit]; // TODO broken
			digit_height = 5;
			digit_width = 6;
		}

		const int y = pos_y + ((grid->box_height - digit_height) / 2);
		const int x = pos_x + ((grid->box_width - digit_amount * digit_width) / 2);
		const int digit_offset = (digit_amount - d - 1) * digit_width;
		for (int i = 0; i < digit_height; i++) {
			mvwprintw(grid->grid_win, y + i, x + digit_offset, "%.*s", digit_width, ascii_art + (i * digit_height));
		}
	}
}

void print_grid(t_grid *grid)
{
	int i = 0;
	int j;
	clear();
	int term_width = getmaxx(stdscr);
	print_score(grid, (term_width - (grid->box_width * grid->size) - 4) / 2);
	mvwin(grid->grid_win, 3, (term_width - (grid->box_width * grid->size) - 4) / 2);
	box(grid->grid_win, 0, 0);
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
		// 	if (*grid_at(grid, i, j) == 0)
		// 	{
		// 		j++;
		// 		continue;
		// 	}
			wattr_on(grid->grid_win, COLOR_PAIR(get_correct_color(*grid_at(grid, i, j))) | A_BOLD, 0);
			int y = i * grid->box_height + 1;
			int x = j * grid->box_width + 2;
			for(int i = 0; i < grid->box_height; i++)
				mvwprintw(grid->grid_win, y + i, x, "%*c", grid->box_width, ' ');
			print_number(grid, *grid_at(grid, i, j), y, x);
			wattr_off(grid->grid_win, COLOR_PAIR(get_correct_color(*grid_at(grid, i, j))), 0);
			j++;
		}
		i++;
	}
	wrefresh(grid->score_win);
	wrefresh(grid->grid_win);
}

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
	int i = rand() % grid->size;
	int j = rand() % grid->size;
	*grid_at(grid, i, j) = 2;
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
			if (*grid_at(grid, i, j) == 8)
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

bool continue_if_term_size_ok(t_grid *grid, int min_height, int min_width)
{
	int y;
	int x;
	getmaxyx(stdscr, y, x);
	while (y < min_height + 5 || x < min_width + 8)
	{
		clear();
		printw("SMALL: y: %d x: %d", y, x);
		int input = getch();
		if (input == 'q' || input == ESCAPE)
			return false;
		getmaxyx(stdscr, y, x);
	}
	clear();
	if (grid)
	{
		refresh();
		delwin(grid->grid_win);
		delwin(grid->score_win);
		init_windows(grid);
		print_grid(grid);
	}
	return true;
}

void game_loop(t_grid *grid)
{
	int input;

	while (1)
	{
		if (!continue_if_term_size_ok(grid, grid->box_height * grid->size, grid->box_width * grid->size))
			return;
		if (validate_if_lost(grid) == 0)
		{
			wprintw(grid->grid_win, "\nGame Over\n");
			wgetch(grid->grid_win);
			break;
		}

		input = wgetch(grid->grid_win);
		if (input == KEY_RESIZE)
		{
			continue;
		}
		if (input != 'i' && input != 'k' && input != 'j' && input != 'l' && input != 'q' && input != ESCAPE
			&& input != 'w' && input != 's' && input != 'a' && input != 'd'
			&& input != KEY_UP && input != KEY_DOWN && input != KEY_LEFT && input != KEY_RIGHT)
		{
			continue;
		}
		if (input == 'i' || input == 'w' || input == KEY_UP)
		{
			if (validate_move(grid, KEY_UP) == 0)
				continue;
			move_up(grid);
			up_merge(grid);
			move_up(grid);
		}
		else if (input == 'k' || input == 's' || input == KEY_DOWN)
		{
			if (validate_move(grid, KEY_DOWN) == 0)
				continue;
			move_down(grid);
			down_merge(grid);
			move_down(grid);
		}
		else if (input == 'j' || input == 'a' || input == KEY_LEFT)
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

		if (is_win_condition(grid))
		{
			print_grid(grid);
			if (!display_win(grid))
				return;
		}
		else 
		{
			spawn_new_number(grid);
		}
	}
}

short rgb_to_ncurses(int rgb)
{
	return (rgb * 1000 / 255);
}

void init_ncurses(void)
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	ESCDELAY = 0;
	curs_set(FALSE);
	start_color();
	use_default_colors();
	init_color(COLOR_EMPTY, rgb_to_ncurses(189), rgb_to_ncurses(172), rgb_to_ncurses(151));
	init_color(COLOR_WHITE, rgb_to_ncurses(255), rgb_to_ncurses(255), rgb_to_ncurses(255));
	init_color(COLOR_DARK, rgb_to_ncurses(117),rgb_to_ncurses(100),rgb_to_ncurses(82));
	init_color(COLOR_2, rgb_to_ncurses(238),rgb_to_ncurses(228),rgb_to_ncurses(219));
	init_pair(COLOR_2, COLOR_DARK, COLOR_2);
	init_color(COLOR_4, rgb_to_ncurses(238),rgb_to_ncurses(224),rgb_to_ncurses(203));
	init_pair(COLOR_4, COLOR_DARK, COLOR_4);
	init_color(COLOR_8, rgb_to_ncurses(243),rgb_to_ncurses(178),rgb_to_ncurses(122));
	init_pair(COLOR_8, COLOR_WHITE, COLOR_8);
	init_color(COLOR_16, rgb_to_ncurses(246),rgb_to_ncurses(150),rgb_to_ncurses(100));
	init_pair(COLOR_16, COLOR_WHITE, COLOR_16);
	init_color(COLOR_32, rgb_to_ncurses(246),rgb_to_ncurses(124),rgb_to_ncurses(95));
	init_pair(COLOR_32, COLOR_WHITE, COLOR_32);
	init_color(COLOR_64, rgb_to_ncurses(247),rgb_to_ncurses(96),rgb_to_ncurses(60));
	init_pair(COLOR_64, COLOR_WHITE, COLOR_64);
	init_color(COLOR_128, rgb_to_ncurses(236),rgb_to_ncurses(208),rgb_to_ncurses(114));
	init_pair(COLOR_128, COLOR_WHITE, COLOR_128);
	init_color(COLOR_256, rgb_to_ncurses(238),rgb_to_ncurses(204),rgb_to_ncurses(98));
	init_pair(COLOR_256, COLOR_WHITE, COLOR_256);
	init_color(COLOR_512, rgb_to_ncurses(238),rgb_to_ncurses(201),rgb_to_ncurses(80));
	init_pair(COLOR_512, COLOR_WHITE, COLOR_512);
	init_color(COLOR_1024, rgb_to_ncurses(237),rgb_to_ncurses(197),rgb_to_ncurses(63));
	init_pair(COLOR_1024, COLOR_WHITE, COLOR_1024);
	init_color(COLOR_2048, rgb_to_ncurses(237),rgb_to_ncurses(193),rgb_to_ncurses(46));
	init_pair(COLOR_2048, COLOR_WHITE, COLOR_2048);
	init_color(COLOR_4096, rgb_to_ncurses(237),rgb_to_ncurses(189),rgb_to_ncurses(30)); //rest is custom
	init_pair(COLOR_4096, COLOR_WHITE, COLOR_4096);
	init_color(COLOR_8192, rgb_to_ncurses(237),rgb_to_ncurses(186),rgb_to_ncurses(20));
	init_pair(COLOR_8192, COLOR_WHITE, COLOR_8192);
	init_color(COLOR_16384, rgb_to_ncurses(237),rgb_to_ncurses(182),rgb_to_ncurses(10));
	init_pair(COLOR_16384, COLOR_WHITE, COLOR_16384);
	init_color(COLOR_32768, rgb_to_ncurses(237),rgb_to_ncurses(178),rgb_to_ncurses(0));
	init_pair(COLOR_32768, COLOR_WHITE, COLOR_32768);
	init_color(COLOR_65536, rgb_to_ncurses(237),rgb_to_ncurses(170),rgb_to_ncurses(0));
	init_pair(COLOR_65536, COLOR_WHITE, COLOR_65536);
	init_color(COLOR_131072, rgb_to_ncurses(237),rgb_to_ncurses(160),rgb_to_ncurses(0));
	init_pair(COLOR_131072, COLOR_WHITE, COLOR_131072);
}

WINDOW *create_win(int size_y, int size_x , int pos_y, int pox_x)
{
	WINDOW *win = newwin(size_y, size_x, pos_y, pox_x);
	keypad(win, TRUE);
	return (win);
}

void init_windows(t_grid *grid)
{
	grid->grid_win = create_win(grid->box_height * grid->size + 2, grid->box_width * grid->size + 4, 3, 0);
	grid->score_win = create_win(3, grid->box_width * grid->size + 4, 0, 0);
}

int main(void)
{
	init_ncurses();
	t_grid grid = {0};
	
	switch (popup_menu("Choose a grid size", (const char *[]){"4x4", "5x5", NULL}, NULL)) {
	case 0:
		grid.size = 4;
		break;
	case 1:
		grid.size = 5;
		break;
	default:
		endwin();
		return 0;
	}

	int grid_data[grid.size][grid.size];
	grid.data = (int *)grid_data;
	if (grid.size == 4)
	{
		grid.box_height = 3;
	}
	else
	{
		grid.box_height = 5;
	}
	grid.box_width = grid.box_height * 2;

	init_windows(&grid);
	init_grid(&grid);
	game_loop(&grid);
	delwin(grid.grid_win);
	delwin(grid.score_win);
	endwin();
}
