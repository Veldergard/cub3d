/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:40:51 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 02:29:29 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strnstr() function locates the first occurrence of the null-termi‐
** nated string little in the string big, where not more than len characters
** are searched. Characters that appear after a ‘\0’ character are not
** searched.
**
** const char *big - string in which to search
** const char *little - string to look for
** size_t len - length of big string
**
** If little is an empty string, big is returned; if little occurs nowhere
** in big, NULL is returned; otherwise a pointer to the first character of
** the first occurrence of little is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!little[i])
		return ((char*)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len && big[i + j]
		&& little[j] && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char*)big + i);
		i++;
	}
	return (NULL);
}
