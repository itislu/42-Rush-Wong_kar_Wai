#ifndef HEADER_H
#define HEADER_H

#include <ncurses.h>
#include "grid.h"

#define ESCAPE 27

enum e_const
{
	WIN_VALUE = 2048
};

enum e_colors 
{
	COLOR_EMPTY = 100,
	COLOR_2,
	COLOR_4,
	COLOR_8,
	COLOR_16,
	COLOR_32,
	COLOR_64,
	COLOR_128,
	COLOR_256,
	COLOR_512,
	COLOR_1024,
	COLOR_2048,
	COLOR_4096,
	COLOR_8192,
	COLOR_16384,
	COLOR_32768,
	COLOR_65536,
	COLOR_131072,
	COLOR_MAX,
	COLOR_BRIGHT,
	COLOR_DARK,
};

/* movement.c */
int left_merge(t_grid *grid);
int move_left(t_grid *grid);
int right_merge(t_grid *grid);
int move_right(t_grid *grid);
int up_merge(t_grid *grid);
int move_up(t_grid *grid);
int down_merge(t_grid *grid);
int move_down(t_grid *grid);
int validate_move(t_grid *grid, int input);

/* ncurses.c */
bool init_ncurses(void);
bool init_windows(t_grid *grid);
void set_box_size(t_grid *grid);
bool continue_if_term_size_ok(t_grid *grid, int min_height, int min_width);

/* print.c */
void print_score(t_grid *grid);
void print_scoreboard(t_grid *grid);
void print_grid(t_grid *grid);
bool display_game_over(t_grid *grid);
bool display_win(t_grid *grid);

#endif
