#include "scoreboard.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static bool is_descending(const void *a, const void *b)
{
	return (long)a >= (long)b;
}

static bool is_valid_score(const char *line)
{
	for (size_t i = 0; line[i]; i++) {
		if (line[i] == '\n') {
			break;
		}
		if (!ft_isdigit(line[i])) {
			return false;
		}
	}
	return ft_isoverflow_long(line) == false;
}

// TODO Print errors
bool read_scorefile(t_scoreboard *scoreboard)
{
	int fd = open(SCORE_FILE, O_RDONLY);
	if (fd == -1) {
		return true;
	}

	t_list *scores = NULL;
	int amount = 0;
	errno = 0;
	char *line;
	while ((line = get_next_line(fd))) {
		if (!is_valid_score(line)) {
			free(line);
			continue;
		}

		long score = ft_atol(line);
		free(line);
		if (!ft_lstnew_front(&scores, (void *)score)) {
			break;
		}
		amount++;
	}
	close(fd);
	if (errno != 0) {
		ft_lstclear(&scores, NULL);
		return false;
	}

	ft_lstsort_merge(
	    &scores,
	    (const void *(*)(const void *, const void *))(long)is_descending);

	scoreboard->scores = malloc(amount * sizeof(t_score));
	if (!scoreboard->scores) {
		ft_lstclear(&scores, NULL);
		return false;
	}
	for (int i = 0; i < amount; i++) {
		scoreboard->scores[i].score = (long)ft_lstpop_front_content(&scores);
	}
	scoreboard->amount = amount;
	return true;
}

bool save_score(long score)
{
	int fd = open(SCORE_FILE,
	              O_CREAT | O_WRONLY | O_APPEND,
	              (S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd == -1) {
		return false;
	}

	ft_dprintf(fd, "\n%d\n", score);
	return true;
}
