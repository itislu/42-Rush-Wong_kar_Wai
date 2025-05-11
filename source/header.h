#ifndef HEADER_H
#define HEADER_H

#include <ncurses.h>
#include "grid.h"

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
	COLOR_DARK,
};

#define ESCAPE 27

enum e_const
{
	WIN_VALUE = 2048
};

void print_grid(t_grid *grid);
void init_windows(t_grid *grid);
bool continue_if_term_size_ok(t_grid *grid, int min_height, int min_width);

#endif
