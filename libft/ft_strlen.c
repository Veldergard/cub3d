/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 04:29:04 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/21 20:51:38 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strlen() function calculates the length of the string pointed to by
** s, excluding the terminating null byte ('\0').
**
** const char *s - string
**
** The strlen() function returns the number of bytes in the string pointed
** to by s.
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
