/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:33:26 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/09 15:56:42 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns an array
** of strings obtained by splitting ’s’ using the
** character ’c’ as a delimiter. The array must be
** ended by a NULL pointer.
**
** char const *s - The string to be split.
** char c - The delimiter character.
**
** The array of new strings resulting from the split.
** NULL if the allocation fails.
*/

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t		counter;
	char		finded;

	counter = 0;
	finded = 1;
	while (*s)
	{
		if (*s == c && !finded)
			finded = 1;
		else if (*s != c && finded)
		{
			if (counter + 1 < counter)
				return (counter - 1);
			counter++;
			finded = 0;
		}
		s++;
	}
	return (counter);
}

static size_t	ft_word_len(char const *s, char c)
{
	size_t		counter;

	counter = 0;
	while (s[counter] && s[counter] != c)
	{
		if (counter + 1 < counter)
			return (counter - 1);
		counter++;
	}
	return (counter);
}

char			**ft_split(char const *s, char c)
{
	char		**result;
	size_t		arr_len;
	size_t		i;
	size_t		j;
	size_t		len;

	if (!s)
		return (NULL);
	arr_len = ft_count_words(s, c);
	if (!(result = (char**)malloc(sizeof(char*) * (arr_len + 1))))
		return (NULL);
	i = 0;
	while (i < arr_len && *s && !(j = 0))
	{
		while (*s == c)
			s++;
		len = ft_word_len(s, c);
		if (!(result[i] = (char*)malloc((len + 1) * sizeof(char))))
			return (ft_clean_array((void**)result, i));
		while (j < len)
			result[i][j++] = *(s++);
		result[i++][j] = '\0';
	}
	result[arr_len] = NULL;
	return (result);
}
