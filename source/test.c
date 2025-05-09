#include "header.h"

int sig = 0;

int	get_correct_color(int num)
{
	if (num == 2)
		return (COLOR_2);
	else if (num == 4)
		return (COLOR_4);
	else if (num == 8)
		return (COLOR_8);
	else if (num == 16)
		return (COLOR_16);
	else if (num == 32)
		return (COLOR_32);
	else if (num == 64)
		return (COLOR_64);
	else if (num == 128)
		return (COLOR_128);
	else if (num == 256)
		return (COLOR_256);
	else if (num == 512)
		return (COLOR_512);
	else if (num == 1024)
		return (COLOR_1024);
	else if (num == 2048)
		return (COLOR_2048);
	else if (num == 4096)
		return (COLOR_4096);
	else if (num == 8192)
		return (COLOR_8192);
	else if (num == 16384)
		return (COLOR_16384);
	else if (num == 32768)
		return (COLOR_32768);
	else if (num == 65536)
		return (COLOR_65536);
	else if (num == 131072)
		return (COLOR_131072);
	return (0);
}

void print_grid(int grid[GRID_SIZE][GRID_SIZE])
{
	int i = 0;
	int j;
	move(0, 0);
	clear();
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
		// 	if (grid[i][j] == 0)
		// 	{
		// 		j++;
		// 		continue;
		// 	}
			attron(COLOR_PAIR(get_correct_color(grid[i][j])) | A_BOLD);
			int y = i * BOX_HEIGHT;
			int x = j * BOX_WIDTH;
			move(y, x);
			printw("      ");
			move(y + 1, x);
			if (grid[i][j] < 10)
				printw("  %d   ", grid[i][j]);
			else if (grid[i][j] < 100)
				printw("  %d  ", grid[i][j]);
			else if (grid[i][j] < 1000)
				printw(" %d  ", grid[i][j]);
			else if (grid[i][j] < 10000)
				printw(" %d ", grid[i][j]);
			else if (grid[i][j] < 100000)
				printw("%d ", grid[i][j]);
			else if (grid[i][j] < 1000000)
				printw("%d", grid[i][j]);
			move(y + 2, x);
			printw("      ");
			attroff(COLOR_PAIR(get_correct_color(grid[i][j])));
			j++;
		}
		i++;
	}
	refresh();
}

void init_grid(int (*grid)[GRID_SIZE][GRID_SIZE])
{
	memset((*grid), 0, sizeof(int) * GRID_SIZE * GRID_SIZE);
	srand(time(NULL));
	// (*grid)[0][0] = 512;
	// (*grid)[0][1] = 1024;
	// (*grid)[0][2] = 2048;
	// (*grid)[0][3] = 4096;
	// (*grid)[1][0] = 8192;
	// (*grid)[1][1] = 16384;
	// (*grid)[1][2] = 32768;
	// (*grid)[1][3] = 65536;
	// (*grid)[2][0] = 131072;
	// (*grid)[2][1] = 262144;
	int i = rand() % GRID_SIZE;
	int j = rand() % GRID_SIZE;
	(*grid)[i][j] = 2;
	while (1)
	{
		i = rand() % GRID_SIZE;
		j = rand() % GRID_SIZE;
		if ((*grid)[i][j] == 0)
		{
			if (rand() % 10 < 9)
				(*grid)[i][j] = 2;
			else
				(*grid)[i][j] = 4;
			break;
		}
	}
}

void spawn_new_number(int grid[GRID_SIZE][GRID_SIZE])
{
	int i;
	int j;
	while (1)
	{
		i = rand() % GRID_SIZE;
		j = rand() % GRID_SIZE;
		if (grid[i][j] == 0)
		{
			if (rand() % 10 < 9)
				grid[i][j] = 2;
			else
				grid[i][j] = 4;
			break;
		}
	}
}

int left_merge(int grid[GRID_SIZE][GRID_SIZE])
{
	int i = 0;
	int j;
	int merged = 0;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j + 1 < GRID_SIZE)
		{
			if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1])
			{
				grid[i][j] = grid[i][j] + grid[i][j + 1];
				grid[i][j + 1] = 0;
				merged = 1;
			}
			j++;
		}
		i++;
	}
	return (merged);
}

int move_left(int grid[GRID_SIZE][GRID_SIZE])
{
	int i = 0;
	int j;
	int l;
	int moved = 0;
	while (i < GRID_SIZE)
	{
		j = 1;
		while (j < GRID_SIZE)
		{
			if (grid[i][j] != 0)
			{
				l = j;
				while (l > 0 && grid[i][l - 1] == 0)
				{
					grid[i][l - 1] = grid[i][l];
					grid[i][l] = 0;
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

int right_merge(int grid[GRID_SIZE][GRID_SIZE])
{
	int i = 0;
	int j;
	int merged = 0;
	while (i < GRID_SIZE)
	{
		j = GRID_SIZE - 1;
		while (j - 1 >= 0)
		{
			if (grid[i][j] != 0 && grid[i][j] == grid[i][j - 1])
			{
				grid[i][j] = grid[i][j] + grid[i][j - 1];
				grid[i][j - 1] = 0;
				merged = 1;
			}
			j--;
		}
		i++;
	}
	return (merged);
}

int move_right(int grid[GRID_SIZE][GRID_SIZE])
{
	int i = 0;
	int j;
	int l;
	int moved = 0;
	while (i < GRID_SIZE)
	{
		j = GRID_SIZE - 2;
		while (j >= 0)
		{
			if (grid[i][j] != 0)
			{
				l = j;
				while (l < GRID_SIZE - 1 && grid[i][l + 1] == 0)
				{
					grid[i][l + 1] = grid[i][l];
					grid[i][l] = 0;
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

int up_merge(int grid[GRID_SIZE][GRID_SIZE])
{
	int j = 0;
	int i;
	int merged = 0;
	while (j < GRID_SIZE)
	{
		i = 0;
		while (i + 1 < GRID_SIZE)
		{
			if (grid[i][j] != 0 && grid[i][j] == grid[i + 1][j])
			{
				grid[i][j] = grid[i][j] + grid[i + 1][j];
				grid[i + 1][j] = 0;
				merged = 1;
			}
			i++;
		}
		j++;
	}
	return (merged);
}

int move_up(int grid[GRID_SIZE][GRID_SIZE])
{
	int j = 0;
	int i;
	int l;
	int moved = 0;
	while (j < GRID_SIZE)
	{
		i = 1;
		while (i < GRID_SIZE)
		{
			if (grid[i][j] != 0)
			{
				l = i;
				while (l > 0 && grid[l - 1][j] == 0)
				{
					grid[l - 1][j] = grid[l][j];
					grid[l][j] = 0;
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

int down_merge(int grid[GRID_SIZE][GRID_SIZE])
{
	int j = 0;
	int i;
	int merged = 0;
	while (j < GRID_SIZE)
	{
		i = GRID_SIZE - 1;
		while (i - 1 >= 0)
		{
			if (grid[i][j] != 0 && grid[i][j] == grid[i - 1][j])
			{
				grid[i][j] = grid[i][j] + grid[i - 1][j];
				grid[i - 1][j] = 0;
				merged = 1;
			}
			i--;
		}
		j++;
	}
	return (merged);
}

int move_down(int grid[GRID_SIZE][GRID_SIZE])
{
	int j = 0;
	int i;
	int l;
	int moved = 0;
	while (j < GRID_SIZE)
	{
		i = GRID_SIZE - 2;
		while (i >= 0)
		{
			if (grid[i][j] != 0)
			{
				l = i;
				while (l < GRID_SIZE - 1 && grid[l + 1][j] == 0)
				{
					grid[l + 1][j] = grid[l][j];
					grid[l][j] = 0;
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

int validate_if_lost(int grid[GRID_SIZE][GRID_SIZE])
{
	int i = 0;
	int j;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			if (grid[i][j] == 0)
				return (1);
			if (i + 1 < GRID_SIZE && grid[i][j] == grid[i + 1][j])
				return (1);
			if (j + 1 < GRID_SIZE && grid[i][j] == grid[i][j + 1])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int validate_move(int grid[GRID_SIZE][GRID_SIZE], int input)
{
	int tmp_grid[GRID_SIZE][GRID_SIZE];
	int i = 0;
	int j;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			tmp_grid[i][j] = grid[i][j];
			j++;
		}
		i++;
	}
	if (input == KEY_UP)
	{
		if (move_up(tmp_grid) == 1)
			return (1);
		if (up_merge(tmp_grid) == 1)
			return (1);
		if (move_up(tmp_grid) == 1)
			return (1);
	}
	else if (input == KEY_DOWN)
	{
		if (move_down(tmp_grid) == 1)
			return (1);
		if (down_merge(tmp_grid) == 1)
			return (1);
		if (move_down(tmp_grid) == 1)
			return (1);
	}
	else if (input == KEY_LEFT)
	{
		if (move_left(tmp_grid) == 1)
			return (1);
		if (left_merge(tmp_grid) == 1)
			return (1);
		if (move_left(tmp_grid) == 1)
			return (1);
	}
	else if (input == KEY_RIGHT)
	{
		if (move_right(tmp_grid) == 1)
			return (1);
		if (right_merge(tmp_grid) == 1)
			return (1);
		if (move_right(tmp_grid) == 1)
			return (1);
	}
	return (0);
}

bool is_win_condition(int grid[GRID_SIZE][GRID_SIZE])
{
	int i = 0;
	int j;
	static bool win = false;

	if (win)
		return (false);
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			if (grid[i][j] == 16)
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

bool display_win()
{
	// int input;
	printw("\n\n        YOU WON");
	printw("\nDo you want to continue? (y/n)");
	/* while (1)
	{
		input = getch();
		if
	} */
	return (true);
}

void game_loop(int grid[GRID_SIZE][GRID_SIZE])
{
	int input;

	while (1)
	{
		if (validate_if_lost(grid) == 0)
		{
			printw("\nGame Over\n");
			getch();
			break;
		}
		input = getch();
		if (input == KEY_RESIZE)
		{
			print_grid(grid);
			continue;
		}
		if (input != 'i' && input != 'k' && input != 'j' && input != 'l' && input != 'q' && input != 27
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
		else if (input == 'q' || input == 27)
		{
			break;
		}
		//if (grid_full(grid) == 0)
		//print_grid(grid);
		if (is_win_condition(grid))
		{
			print_grid(grid);
			display_win();
		}
		else 
		{
			spawn_new_number(grid);
		print_grid(grid);
		}
	}
}

short rgb_to_ncurses(int rgb)
{
	return (rgb * 1000 / 255);
}

void init_ncurses()
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	ESCDELAY = 0;
	curs_set(FALSE);
	start_color();
	use_default_colors();
	init_color(COLOR_WHITE, rgb_to_ncurses(255), rgb_to_ncurses(255), rgb_to_ncurses(255));
	init_pair(1, COLOR_WHITE, -1);
	init_color(COLOR_2, rgb_to_ncurses(238),rgb_to_ncurses(228),rgb_to_ncurses(219));
	init_pair(COLOR_2, COLOR_WHITE, COLOR_2);
	init_color(COLOR_4, rgb_to_ncurses(238),rgb_to_ncurses(224),rgb_to_ncurses(203));
	init_pair(COLOR_4, COLOR_WHITE, COLOR_4);
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

int main()
{
	int grid[GRID_SIZE][GRID_SIZE];

	init_ncurses();
	init_grid(&grid);
	print_grid(grid);
	game_loop(grid);
	endwin();
}
