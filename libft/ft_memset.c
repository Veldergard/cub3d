/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:11:20 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 02:25:06 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_memset fills the first n  bytes of the memory area
** pointed to by s with the constant byte c.
**
** void *s - memory area
** int c - constant byte
** size_t n - number of bytes to fill
**
** The ft_memset() function returns a pointer to the memory area s.
*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ucs;

	i = 0;
	ucs = (unsigned char*)s;
	while (i != n)
		ucs[i++] = (unsigned char)c;
	return (s);
}
