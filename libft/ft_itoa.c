/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 01:29:20 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/09 16:11:25 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a string
** representing the integer received as an argument.
** Negative numbers must be handled.
**
** int n - the integer to convert.
**
** Return the string representing the integer. NULL if the
** allocation fails.
*/

#include "libft.h"

static size_t	num_len(int n)
{
	size_t			len;
	long long int	nb;

	nb = ft_abs_l(n);
	if (nb == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char			*result;
	size_t			len;
	long long int	nb;

	nb = ft_abs_l(n);
	len = num_len(n);
	if (!(result = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	result[len--] = '\0';
	if (n == 0)
		result[len] = '0';
	while (nb > 0)
	{
		result[len--] = '0' + nb % 10;
		nb /= 10;
	}
	if (n < 0)
		result[len] = '-';
	return (result);
}
