/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 01:23:47 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 21:17:20 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_memchr() function scans the  initial n bytes of the memory area
** pointed to by s for the first instance of c. Both c and the bytes of
** the memory area pointed to by s are interpreted as unsigned char.
**
** const void *s - memory area
** int c - byte to find
** size_t n - number of bytes to scan
**
** The ft_memchr() function return a pointer to the matching
** byte or NULL if the character does not occur in the given memory area.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ucs;

	i = 0;
	ucs = (unsigned char*)s;
	while (i < n)
	{
		if (ucs[i] == (unsigned char)c)
			return ((void*)ucs + i);
		i++;
	}
	return (NULL);
}
