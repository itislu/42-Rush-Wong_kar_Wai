/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:36:36 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:45:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * The ft_strrplc_sequence function replaces all occurrences of a sequence in a
 * string with a replacement string.
 *
 * @param str         The string in which to replace the sequence.
 * @param sequence    The sequence to replace in the string.
 * @param rplcmt      The string to replace the sequence with.
 *
 * @return            A new string with all occurrences of the sequence replaced
 *                    with the replacement string.
 *                    If an error occurs, NULL is returned.
 * 				      If str and the replacement string are NULL, the function
 *                    also returns NULL.
 *                    If just the replacement string is not NULL, the function
 *                    returns a copy of the replacement string.
 *                    If str is not NULL but sequence is NULL or an empty
 *                    string or the replacement string is NULL, the function
 *                    returns a copy of the original string.
 *                    If the sequence is not found in str, the function also
 * 				      returns a copy of the original string.
 */
char	*ft_strrplc_sequence(const char *str, const char *sequence,
								const char *rplcmt)
{
	const char	*occurrence;
	char		*result;
	size_t		rplcmt_len;
	size_t		seq_len;

	if (str == NULL && sequence == NULL && rplcmt != NULL)
		return (ft_strdup(rplcmt));
	if (str == NULL)
		return (NULL);
	result = ft_strdup(str);
	if (result == NULL)
		return (NULL);
	if (sequence == NULL || *sequence == '\0' || rplcmt == NULL)
		return (result);
	rplcmt_len = ft_strlen(rplcmt);
	seq_len = ft_strlen(sequence);
	occurrence = ft_strnstr(result, sequence, ft_strlen(result));
	while (occurrence != NULL)
	{
		if (!ft_strrplc_part(&result, rplcmt, occurrence - result, seq_len))
			return (free(result), NULL);
		occurrence = ft_strnstr(occurrence + rplcmt_len, sequence,
				ft_strlen(occurrence + rplcmt_len));
	}
	return (result);
}
