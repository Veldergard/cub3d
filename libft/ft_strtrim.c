/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 02:57:17 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 16:52:12 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc()) and returns a copy of
** ’s1’ with the characters specified in ’set’ removed
** from the beginning and the end of the string.
**
** char const *s1 - The string to be trimmed.
** char const *set - The reference set of characters to trim.
**
** Return the trimmed string. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_is_in_set(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len - 1 < len && ft_is_in_set(s1[len - 1], set))
		len--;
	if (!(trimmed = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimmed[i] = s1[i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
