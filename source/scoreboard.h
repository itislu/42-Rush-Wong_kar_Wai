#ifndef SCOREBOARD_H
# define SCOREBOARD_H

# include <ncurses.h>

# define SCORE_FILE_4x4 "./scores_4x4"
# define SCORE_FILE_5x5 "./scores_5x5"

typedef struct s_score 
{
	long score;
} t_score;

typedef struct s_scoreboard
{
	t_score *scores;
	int amount;
	WINDOW *win;
	int win_height;
	int win_width;
} t_scoreboard;

bool read_scorefile(t_scoreboard *scoreboard, int mode);
bool save_score(long score, int mode);

#endif
