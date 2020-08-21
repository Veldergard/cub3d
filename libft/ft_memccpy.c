/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:26:05 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 03:34:00 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_memccpy() function copies no more than n bytes from memory area src
** to memory area dest, stopping when the character c is found.
**
** If the memory areas overlap, the results are undefined.
**
** void *dest - destination memory area
** const void *src - source memory area
** int c - stop copy character
** size_t n - number of bytes to copy
**
** The ft_memccpy() function returns a pointer to the next character in dest
** after c, or NULL if c was not found in the first n characters of src.
*/

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ucsrc;
	unsigned char		*ucdest;

	if (!src && !dest)
		return (NULL);
	i = 0;
	ucsrc = (unsigned char*)src;
	ucdest = (unsigned char*)dest;
	while (i < n)
	{
		ucdest[i] = ucsrc[i];
		if (ucdest[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
