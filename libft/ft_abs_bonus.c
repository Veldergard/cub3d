/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 02:06:56 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 17:59:11 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_abs_l(long long int n)
{
	return (n > 0 ? n : -n);
}

long int		ft_abs_i(long int n)
{
	if (n == -2147483648)
		return (2147483647);
	return (n > 0 ? n : -n);
}

short int		ft_abs_s(short int n)
{
	if (n == -32768)
		return (32767);
	return (n > 0 ? n : -n);
}

char			ft_abs_c(char n)
{
	if (n == -128)
		return (127);
	return (n > 0 ? n : -n);
}
