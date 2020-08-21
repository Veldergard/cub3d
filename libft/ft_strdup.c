/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 21:07:28 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/09 16:24:07 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strdup() function returns  a pointer to a new string which
** is a duplicate of the string s. Memory for the new string
** is obtained with malloc(), and can be freed with free().
**
** On success, the ft_strdup() function returns a pointer
** to the duplicated string.  It returns NULL if insufficient
** memory was available, with errno set to indicate the
** cause of the error.
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		i;
	char		*result;

	i = 0;
	while (s[i])
		i++;
	result = (char*)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
