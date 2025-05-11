#ifndef SCOREBOARD_H
# define SCOREBOARD_H

# include <ncurses.h>

typedef struct s_score 
{
	unsigned int score;
} t_score;

typedef struct s_scoreboard
{
	t_score *scores;
	int amount;
	WINDOW *win;
	int win_height;
	int win_width;
	// int min_width;
} t_scoreboard;

#endif
