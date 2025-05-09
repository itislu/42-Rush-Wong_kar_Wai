#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "libft/libft.h"
#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>

#define GRID_SIZE 4
#define BOX_HEIGHT 3
#define BOX_WIDTH 6

#define COLOR_2 2
#define COLOR_4 3
#define COLOR_8 4
#define COLOR_16 5
#define COLOR_32 6
#define COLOR_64 8
#define COLOR_128 9
#define COLOR_256 10
#define COLOR_512 11
#define COLOR_1024 12
#define COLOR_2048 13
#define COLOR_4096 14
#define COLOR_8192 15
#define COLOR_16384 16
#define COLOR_32768 17
#define COLOR_65536 18
#define COLOR_131072 19

enum e_const
{
	WIN_VALUE = 2048
};

#endif