/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 06:39:49 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 19:21:42 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strlcat() function concatenate strings respectively.
** It is designed to be safer, more consistent, and less error
** prone replacement for strncat. Unlike that function,
** ft_strlcat() take the full size of the buffer (not just
** the length) and guarantee to NUL-terminate the result (as long
** as there is at least one byte free in dst). Note that a
** byte for the NUL should be included in size. Also note
** that ft_strlcat() only operate on true “C” strings. This
** means that for ft_strlcat() both src and dst must be NUL-terminated.
**
** The ft_strlcat() function appends the NUL-terminated string src to the end
** of dst. It will append at most size - strlen(dst) - 1 bytes, NUL-termi‐
** nating the result.
**
** char *dst - destination string
** const char *src - source string
** size_t size - full size of the dest
**
** The ft_strlcat() function return the total length of the string
** it tried to create. For ft_strlcat() that means the initial
** length of dst plus the length of src. While this may seem
** somewhat confusing, it was done to make truncation detection simple.
**
** Note, however, that if ft_strlcat() traverses size characters without find‐
** ing a NUL, the length of the string is considered to be size and the des‐
** tination string will not be NUL-terminated (since there was no space for
** the NUL).  This keeps ft_strlcat() from running off the end of a string.  In
** practice this should not happen (as it means that either size is incor‐
** rect or that dst is not a proper “C” string).  The check exists to pre‐
** vent potential security problems in incorrect code.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dst_size;
	size_t src_size;

	i = 0;
	while (dst[i])
		i++;
	dst_size = i;
	src_size = 0;
	if (size > i)
		while (src[src_size] && size - i > 1)
			dst[i++] = src[src_size++];
	dst[i] = '\0';
	while (src[src_size])
		src_size++;
	return ((dst_size < size ? dst_size : size) + src_size);
}
