/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:47:58 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/06 19:50:34 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_atoi() function converts the initial portion of the string pointed
** to by nptr to int. The behavior is the same as
**
** strtol(nptr, NULL, 10);
**
** except that ft_atoi() does not detect errors.
**
** const char *nptr - string with number which needed to convert to int
**
** Returns converted value.
*/

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	int numb;
	int porn;

	porn = 1;
	while (*nptr && ((*nptr >= 9 && *nptr <= 13) || *nptr == ' '))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		porn = *nptr == '-' ? -1 : 1;
		nptr++;
	}
	numb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (numb < 0 && porn < 0)
			return (0);
		else if (numb < 0 && porn > 0)
			return (-1);
		numb = (numb * 10) + (*nptr - '0');
		nptr++;
	}
	return (numb * porn);
}
