#include "header.h"
#include "libft/libft.h"
#include <menu.h>
#include <ncurses.h>

/**
 * Returns the index of the chosen option, or -1 on exit.
 * `options` is expected to be a NULL-terminated array of strings.
 */
int popup_menu(const char *title, const char *options[])
{
	const int title_len = ft_strlen(title);
	int max_len = title_len;
	int option_amount = 0;
	for (int i = 0; options[i]; i++) {
		max_len = ft_max(ft_strlen(options[i]), max_len);
		option_amount++;
	}

	const int term_height = getmaxy(stdscr);
	const int term_width = getmaxx(stdscr);
	const int height = option_amount + 4 /*padding*/;
	const int width = max_len + 6 /*padding*/;

	WINDOW *win = newwin(
	    height, width, (term_height - height) / 2, (term_width - width) / 2);
	box(win, 0, 0);
	refresh();
	keypad(win, true);

	mvwprintw(win, 0, (width - title_len) / 2, " %s ", title);

	int cur_option = 0;
	while (true) {
		for (int i = 0; i < option_amount; i++) {
			if (i == cur_option) {
				wattron(win, A_REVERSE);
			}
			mvwprintw(win, 2 + i, 2, "%*s", width - 4, options[i]);
			if (i == cur_option) {
				wattroff(win, A_REVERSE);
			}
		}
		wrefresh(win);

		while (true) {
			switch (getch()) {
			case KEY_DOWN:
				cur_option = ft_min(cur_option + 1, option_amount - 1);
				goto inner_end;
			case KEY_UP:
				cur_option = ft_max(cur_option - 1, 0);
				goto inner_end;
			case '\n':
			case KEY_RIGHT:
				goto outer_end;
			case 'q':
			case ESCAPE:
				cur_option = -1;
				goto outer_end;
			}
		}
	inner_end:;
	}
outer_end:

	delwin(win);
	return cur_option;
}
