/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:27:20 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 03:32:56 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_memcpy() function copies n bytes from memory area src to memory
** area dest. The memory areas must not overlap. Use ft_memmove if the
** memory areas do overlap.
**
** void *dest - destination memory area
** const void *src - source memory area
** size_t n - number of bytes to copy
**
** The ft_memcpy() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*ucsrc;
	unsigned char		*ucdest;

	if (!src && !dest)
		return (NULL);
	ucsrc = (unsigned char*)src;
	ucdest = (unsigned char*)dest;
	i = 0;
	while (i < n)
	{
		ucdest[i] = ucsrc[i];
		i++;
	}
	return (dest);
}
