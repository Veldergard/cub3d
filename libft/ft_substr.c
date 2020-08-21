/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 23:16:54 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/09 18:33:25 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc()) and returns a substring
** from the string ’s’.
** The substring begins at index ’start’ and is of
** maximum size ’len’.
**
** char const *s - The string from which to create the substring.
** unsigned int start - The start index of the substring in the string ’s’.
** size_t len - The maximum length of the substring.
**
** Return the substring. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		i;
	size_t		strlen;

	strlen = s ? ft_strlen(s) : 0;
	if (strlen < start)
		len = 0;
	if (len > strlen - start)
		len = strlen - start;
	if (!(substr = (char*)malloc(sizeof(*substr) * (len + 1))))
		return (NULL);
	i = 0;
	s += start;
	while (i < len)
	{
		substr[i] = s[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
