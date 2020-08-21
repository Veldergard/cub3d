/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 08:11:15 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/21 23:58:59 by olaurine         ###   ########.fr       */
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
	if (!s)
		return (NULL);
	while (*s && *s != c)
		s++;
	if (*s == (char)c)
		return ((char*)s);
	return (NULL);
}
