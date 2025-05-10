#include "header.h"
#include "libft/libft.h"
#include <ncurses.h>
#include "grid.h"

/**
 * Returns the index of the chosen option, or -1 on exit.
 * `options` is expected to be a NULL-terminated array of strings.
 */
int popup_menu(const char *title, const char *options[], t_grid *grid)
{
	const int title_len = ft_strlen(title);
	int max_len = title_len;
	int option_amount = 0;
	for (int i = 0; options[i]; i++) {
		max_len = ft_max(ft_strlen(options[i]), max_len);
		option_amount++;
	}
	
	int cur_option = 0;
	while (true) {
		int term_height;
		const int term_width = getmaxx(stdscr);
		if (grid)
			term_height = getmaxy(grid->grid_win) + grid->size + 2;
		else
			term_height = getmaxy(stdscr);
		const int height = option_amount + 4 /*padding*/;
		const int width = max_len + 6 /*padding*/;

		clear();
		if (grid)
		{
			if (!continue_if_term_size_ok(grid, grid->box_height * grid->size, grid->box_width * grid->size))
				return -1;
		}
		else 
		{
			if (!continue_if_term_size_ok(grid, height, width))
				return -1;
		}

		WINDOW *win = newwin(
			height, width, (term_height - height) / 2, (term_width - width) / 2);
		box(win, 0, 0);
		keypad(win, true);
	
		mvwprintw(win, 0, (width - title_len - 2 /*spaces*/) / 2, " %s ", title);
		for (int i = 0; i < option_amount; i++) {
			if (i == cur_option) {
				wattron(win, A_REVERSE);
			}
			mvwprintw(win, 2 + i, 2, "%*s", width - 4, options[i]);
			if (i == cur_option) {
				wattroff(win, A_REVERSE);
			}
		}
		if (grid)
		{
			touchwin(grid->score_win);
			touchwin(grid->grid_win);
		}
		touchwin(win);
		refresh();
		if (grid)
		{
			wrefresh(grid->score_win);
			wrefresh(grid->grid_win);
		}
		wrefresh(win);

		while (true) {
			switch (getch()) {
			case KEY_RESIZE:
				goto end;
			case KEY_DOWN:
				cur_option = ft_min(cur_option + 1, option_amount - 1);
				goto end;
			case KEY_UP:
				cur_option = ft_max(cur_option - 1, 0);
				goto end;
			case '\n':
			case KEY_RIGHT:
				return cur_option;
			case 'q':
			case ESCAPE:
				return -1;
			}
		}
	end:;
	delwin(win);
	}

}
