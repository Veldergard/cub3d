/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 01:55:49 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/09 16:07:36 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_memcmp() function compares the first n bytes (each interpreted as
** unsigned char) of the memory areas s1 and s2.
**
** const void *s1 - first memory area
** const void *s2 - second memory area
** size_t n - number of bytes to compare
**
** The ft_memcmp() function returns an integer less than, equal to, or
** greater than zero if the first n bytes of s1 is found, respectively, to
** be less than, to match, or be greater than the first n bytes of s2.
**
** For a nonzero return value, the sign is determined by the sign of the
** difference between the first pair of bytes (interpreted as unsigned
** char) that differ in s1 and s2.
**
** If n is zero, the return value is zero.
*/

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*ucs1;
	unsigned char		*ucs2;

	i = 0;
	ucs1 = (unsigned char*)s1;
	ucs2 = (unsigned char*)s2;
	while (i < n)
	{
		if (ucs1[i] != ucs2[i])
			return (ucs1[i] - ucs2[i]);
		i++;
	}
	return (0);
}
