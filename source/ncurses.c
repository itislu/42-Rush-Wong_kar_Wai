#include "header.h"
#include "grid.h"
#include "libft/libft.h"
#include <ncurses.h>

static short rgb_to_ncurses(int rgb)
{
	return (rgb * 1000 / 255);
}

bool init_ncurses(void)
{
	if (!initscr()) {
		return false;
	}
	noecho();
	keypad(stdscr, TRUE);
	ESCDELAY = 0;
	curs_set(FALSE);
	start_color();
	use_default_colors();
	init_color(COLOR_BRIGHT, rgb_to_ncurses(255), rgb_to_ncurses(255), rgb_to_ncurses(255));
	init_color(COLOR_DARK, rgb_to_ncurses(117),rgb_to_ncurses(100),rgb_to_ncurses(82));
	init_color(COLOR_EMPTY, rgb_to_ncurses(189), rgb_to_ncurses(172), rgb_to_ncurses(151));
	init_pair(COLOR_EMPTY, COLOR_DARK, COLOR_EMPTY);
	init_color(COLOR_2, rgb_to_ncurses(238),rgb_to_ncurses(228),rgb_to_ncurses(219));
	init_pair(COLOR_2, COLOR_DARK, COLOR_2);
	init_color(COLOR_4, rgb_to_ncurses(238),rgb_to_ncurses(224),rgb_to_ncurses(203));
	init_pair(COLOR_4, COLOR_DARK, COLOR_4);
	init_color(COLOR_8, rgb_to_ncurses(243),rgb_to_ncurses(178),rgb_to_ncurses(122));
	init_pair(COLOR_8, COLOR_BRIGHT, COLOR_8);
	init_color(COLOR_16, rgb_to_ncurses(246),rgb_to_ncurses(150),rgb_to_ncurses(100));
	init_pair(COLOR_16, COLOR_BRIGHT, COLOR_16);
	init_color(COLOR_32, rgb_to_ncurses(246),rgb_to_ncurses(124),rgb_to_ncurses(95));
	init_pair(COLOR_32, COLOR_BRIGHT, COLOR_32);
	init_color(COLOR_64, rgb_to_ncurses(247),rgb_to_ncurses(96),rgb_to_ncurses(60));
	init_pair(COLOR_64, COLOR_BRIGHT, COLOR_64);
	init_color(COLOR_128, rgb_to_ncurses(236),rgb_to_ncurses(208),rgb_to_ncurses(114));
	init_pair(COLOR_128, COLOR_BRIGHT, COLOR_128);
	init_color(COLOR_256, rgb_to_ncurses(238),rgb_to_ncurses(204),rgb_to_ncurses(98));
	init_pair(COLOR_256, COLOR_BRIGHT, COLOR_256);
	init_color(COLOR_512, rgb_to_ncurses(238),rgb_to_ncurses(201),rgb_to_ncurses(80));
	init_pair(COLOR_512, COLOR_BRIGHT, COLOR_512);
	init_color(COLOR_1024, rgb_to_ncurses(237),rgb_to_ncurses(197),rgb_to_ncurses(63));
	init_pair(COLOR_1024, COLOR_BRIGHT, COLOR_1024);
	init_color(COLOR_2048, rgb_to_ncurses(237),rgb_to_ncurses(193),rgb_to_ncurses(46));
	init_pair(COLOR_2048, COLOR_BRIGHT, COLOR_2048);
	init_color(COLOR_4096, rgb_to_ncurses(237),rgb_to_ncurses(189),rgb_to_ncurses(30)); //rest is custom
	init_pair(COLOR_4096, COLOR_BRIGHT, COLOR_4096);
	init_color(COLOR_8192, rgb_to_ncurses(237),rgb_to_ncurses(186),rgb_to_ncurses(20));
	init_pair(COLOR_8192, COLOR_BRIGHT, COLOR_8192);
	init_color(COLOR_16384, rgb_to_ncurses(237),rgb_to_ncurses(182),rgb_to_ncurses(10));
	init_pair(COLOR_16384, COLOR_BRIGHT, COLOR_16384);
	init_color(COLOR_32768, rgb_to_ncurses(237),rgb_to_ncurses(178),rgb_to_ncurses(0));
	init_pair(COLOR_32768, COLOR_BRIGHT, COLOR_32768);
	init_color(COLOR_65536, rgb_to_ncurses(237),rgb_to_ncurses(170),rgb_to_ncurses(0));
	init_pair(COLOR_65536, COLOR_BRIGHT, COLOR_65536);
	init_color(COLOR_131072, rgb_to_ncurses(237),rgb_to_ncurses(160),rgb_to_ncurses(0));
	init_pair(COLOR_131072, COLOR_BRIGHT, COLOR_131072);
	init_color(COLOR_MAX, rgb_to_ncurses(57),rgb_to_ncurses(55),rgb_to_ncurses(47));
	init_pair(COLOR_MAX, COLOR_BRIGHT, COLOR_MAX);
	return true;
}

static WINDOW *create_win(int size_y, int size_x , int pos_y, int pox_x)
{
	WINDOW *win = newwin(size_y, size_x, pos_y, pox_x);
	keypad(win, TRUE);
	return (win);
}

void init_windows(t_grid *grid)
{
	int term_width = getmaxx(stdscr);
	grid->grid_win_width = grid->box_width * grid->size + 4 /*frame*/;
	int total_width = grid->grid_win_width;
	if (grid->scoreboard->amount > 0) {
		total_width += 1 + grid->scoreboard->win_width;
	}
		
	grid->score_win_pos_x = (term_width - total_width) / 2;
	grid->score_win_pos_y = 0;
	grid->score_win_height = 3;
	grid->grid_win_pos_x = grid->score_win_pos_x;
	grid->grid_win_pos_y = grid->score_win_height;
	grid->grid_win_height = grid->box_height * grid->size + 2 /*frame*/;
	grid->score_win_width = grid->grid_win_width;
	grid->scoreboard->win_height = grid->score_win_height + grid->grid_win_height;
	
	grid->score_win = create_win(grid->score_win_height, grid->score_win_width, grid->score_win_pos_y, grid->score_win_pos_x);
	if (!grid->score_win) {
		return;
	}
	grid->grid_win = create_win(grid->grid_win_height, grid->grid_win_width, grid->grid_win_pos_y, grid->grid_win_pos_x);
	if (!grid->grid_win) {
		delwin(grid->score_win);
		return;
	}
	if (grid->scoreboard->amount > 0)
	{
		grid->scoreboard->win = create_win(grid->scoreboard->win_height, grid->scoreboard->win_width, grid->score_win_pos_y, grid->grid_win_pos_x + grid->grid_win_width + 1 /*spacing*/);
		if (!grid->scoreboard->win) {
			delwin(grid->score_win);
			delwin(grid->grid_win);
			return;
		}
	}
}

void set_box_size(t_grid *grid)
{
	int y;
	int x;
	getmaxyx(stdscr, y, x);

	int width_from_grid = (x - grid->width_extra) / grid->size;
	int height_from_grid = (y - grid->height_extra) / grid->size;
	if (height_from_grid % 2 == 0) {
		height_from_grid--; // make it uneven
	}

	int height_from_width = width_from_grid / 2;
	if (height_from_width % 2 == 0) {
		height_from_width--; // make it uneven
	}

	grid->box_height = ft_min(height_from_grid, height_from_width);
	grid->box_width = grid->box_height * 2;
}

bool continue_if_term_size_ok(t_grid *grid, int min_height, int min_width)
{
	int y;
	int x;
	getmaxyx(stdscr, y, x);
	while (y < min_height || x < min_width)
	{
		clear();
		mvprintw(0, 0, "TERMINAL TOO SMALL");
		mvprintw(1, 0, "  minimum: y: %d x: %d", min_height, min_width);
		mvprintw(2, 0, "  current: y: %d x: %d", y, x);
		int input = ft_tolower(getch());
		if (input == 'q' || input == ESCAPE)
			return false;
		getmaxyx(stdscr, y, x);
	}
	clear();
	if (grid)
	{
		set_box_size(grid);
		refresh();
		delwin(grid->grid_win);
		delwin(grid->score_win);
		delwin(grid->scoreboard->win);
		init_windows(grid);
		print_grid(grid);
	}
	return true;
}
