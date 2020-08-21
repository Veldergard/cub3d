/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 04:34:49 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 02:47:04 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strlcpy() function copy string respectively
** It is designed to be safer, more consistent, and less error
** prone replacement for strncpy. Unlike that func‐
** tion, ft_strlcpy() take the full size of the buffer (not just
** the length) and guarantee to NUL-terminate the result (as long as size is
** larger than 0). Note that a byte for the NUL should be included
** in size. Also note that ft_strlcpy() and strlcat() only operate on true “C”
** strings. This means that src must be NUL-terminated
**
** The ft_strlcpy() function copies up to size - 1 characters from the NUL-ter‐
** minated string src to dst, NUL-terminating the result.
**
** char *dst - destination string
** const char *src - source string
** size_t size - full size of the dest
**
** The ft_strlcpy() function return the total length of the
** string they tried to create. For ft_strlcpy() that means the length of src.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (i < size - 1 && size > 0 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
