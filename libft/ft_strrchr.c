/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 08:52:47 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 18:23:16 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strrchr() function returns a pointer to the last occurrence of the
** character c in the string s.
**
** Here "character" means "byte"; these functions do not work with wide or
** multibyte characters.
**
** const char *s - string
** int c - character(byte) to find
**
** The ft_strrchr() function return a pointer to the matched
** character or NULL if the character is not found. The terminating null
** byte is considered part of the string, so that if c is specified as
** '\0', these functions return a pointer to the terminator.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	last_index;
	int		finded;
	size_t	cur;

	cur = 0;
	finded = 0;
	last_index = 0;
	while (s[cur])
	{
		if (s[cur] == c)
		{
			finded = 1;
			last_index = cur;
		}
		cur++;
	}
	if (s[cur] == c)
		return ((char*)s + cur);
	else if (finded)
		return ((char*)s + last_index);
	else
		return (NULL);
}
