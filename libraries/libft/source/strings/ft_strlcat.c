/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:15:16 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:44:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_strlcat function appends the NUL-terminated string src to the end of
 * dst.
 * It will append at most size - strlen(dst) - 1 characters.
 * It will then NUL-terminate, unless size is 0 or the original dst string was
 * longer than size.
 *
 * @param dst     The string to be appended to.
 * @param src     The string to append to dst.
 * @param size    The total size of dst, including the space for the
 *                NUL-terminator.
 *
 * @return        The total length of the string it tried to create, that means
 *                the initial length of dst plus the length of src.
 *                If the return value is >= size, the output string has been
 *                truncated.
 *
 * @note          Calling ft_strlcat with dst equal to NULL with a size not 0,
 *                or with src equal to NULL, is undefined behavior (mirrors the 
 *                behavior of the original strlcat).
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	catlen;
	size_t	dstlen;
	size_t	srclen;

	if (dst == NULL && size == 0 && src != NULL)
		return (0);
	dstlen = ft_strlen(dst);
	catlen = dstlen;
	srclen = 0;
	while (catlen + 1 < size && src[srclen] != '\0')
	{
		dst[catlen] = src[srclen];
		catlen++;
		srclen++;
	}
	if (dstlen < size)
		dst[catlen] = '\0';
	while (src[srclen] != '\0')
		srclen++;
	if (size < dstlen)
		return (size + srclen);
	return (dstlen + srclen);
}
