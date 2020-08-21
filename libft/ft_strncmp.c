/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:24:13 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/09 17:53:54 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strncmp() function compares compares only the first
** (at most) n bytes of s1 and s2
**
** ft_strncmp() returns an integer indicating the result of the comparison, as
** follows:
**
** • 0, if the s1 and s2 are equal;
**
** • a negative value if s1 is less than s2;
**
** • a positive value if s1 is greater than s2;
**
** const char *s1
** const char *s2
** size_t n
**
** The ft_strncmp() function return an integer less than, equal
** to, or greater than zero if s1 (or the first n bytes thereof) is found,
** respectively, to be less than, to match, or be greater than s2.
*/

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t					i;
	const unsigned char		*ucs1;
	const unsigned char		*ucs2;

	i = 0;
	ucs1 = (unsigned char*)s1;
	ucs2 = (unsigned char*)s2;
	while (i < n && ucs1[i] && ucs2[i] && ucs1[i] == ucs2[i])
		i++;
	if (i == n)
		return (0);
	return ((ucs1[i] - ucs2[i]));
}
