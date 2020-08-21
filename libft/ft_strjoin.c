/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:40:19 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/21 20:54:00 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a new
** string, which is the result of the concatenation
** of ’s1’ and ’s2’.
**
** char const *s1 - The prefix string.
** char const *s2 - The suffix string.
**
** Return the new string. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	len_sum;
	size_t	i;
	char	*s;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len_sum = len1 + len2;
	if (len_sum < (len1 | len2))
		return (NULL);
	if (!(s = (char*)malloc((len_sum + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len1)
		s[i] = s1[i];
	i = 0;
	while (i < len2)
		s[len1++] = s2[i++];
	s[len1] = '\0';
	return (s);
}
