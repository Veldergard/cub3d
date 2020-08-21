/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 00:07:39 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 17:13:35 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_memmove() function copies n bytes from memory area src to memory
** area dest. The memory areas may overlap: copying takes place as though
** the bytes in src are first copied into a temporary array that does not
** overlap src or dest, and the bytes are then copied from the temporary
** array to dest.
**
** void *dest - destination memory area
** const void *src - source memory area
** size_t n - number of bytes to move
**
** The ft_memmove() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*ucsrc;
	unsigned char		*ucdest;

	if (!src && !dest)
		return (NULL);
	i = 0;
	ucsrc = (unsigned char*)src;
	ucdest = (unsigned char*)dest;
	if (ucsrc > ucdest)
	{
		while (i < n)
		{
			ucdest[i] = ucsrc[i];
			i++;
		}
	}
	else
	{
		while (++i <= n)
			ucdest[n - i] = ucsrc[n - i];
	}
	return (dest);
}
