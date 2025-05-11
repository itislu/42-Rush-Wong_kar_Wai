#include "scoreboard.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include <errno.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// void *ft_realloc(void *ptr, size_t size)
// {
// 	void	*new_ptr;

// 	new_ptr = malloc(size);
// 	if (new_ptr == NULL)
// 		return (NULL);
// 	if (ptr != NULL)
// 	{
// 		free(ptr);
// 		ft_memcpy(new_ptr, ptr, size_t n)
// 	}
// }

t_score *new_score(long value)
{
	t_score *score = malloc(sizeof(t_score));
	if (!score) {
		return NULL;
	}
	score->score = value;
	return score;
}

void free_score(t_score *score)
{
	free(score);
}

bool is_descending(const void *a, const void *b)
{
	return (long)a >= (long)b;
}

// void *ft_realloc(void *ptr, size_t new_size, size_t old_size)
// {
// 	void *new_ptr = malloc(new_size);
// 	if (new_ptr == NULL) {
// 		return (NULL);
// 	}
// 	if (ptr != NULL) {
// 		ft_memcpy(new_ptr, ptr, ft_min_u(new_size, old_size));
// 		free(ptr);
// 	}
// 	return (new_ptr);
// }

static bool is_valid_score(const char *line)
{
	for (size_t i = 0; line[i]; i++)  {
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
		return false;
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
		// t_score *score = new_score(ft_atol(line));
		// if (!score) {
		// 	break;
		// }
		if (!ft_lstnew_front(&scores, (void *)score)) {
			// free_score(score);
			break;
		}
		amount++;
	}
	close(fd);
	if (errno != 0) {
		ft_lstclear(&scores, NULL);
		return false;
	}

	ft_lstsort_merge(&scores, (const void *(*)(const void *, const void *))(long)is_descending);

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
