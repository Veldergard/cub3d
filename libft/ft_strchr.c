/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 08:11:15 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 20:12:29 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The  ft_strchr() function returns a pointer to the first occurrence of the
** character c in the string s.
**
** Here "character" means "byte"; these functions do not work with wide or
** multibyte characters.
**
** const char *s - string
** int c - character(byte) to find
**
** The ft_strchr() function return a pointer to the matched
** character or NULL if the character is not found. The terminating null
** byte is considered part of the string, so that if c is specified as
** '\0', these functions return a pointer to the terminator.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char*)s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char*)s + i);
	return (NULL);
}
