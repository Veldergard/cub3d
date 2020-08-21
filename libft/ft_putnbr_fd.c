/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 01:45:58 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/06 19:56:57 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs the integer ’n’ to the given file
** descriptor.
**
** #1. The integer to output.
** #2. The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n / 10 == 0)
		ft_putchar_fd('0' + ft_abs_i(n % 10), fd);
	else
	{
		ft_putnbr_fd((n / 10) * (n < 0 ? -1 : 1), fd);
		ft_putchar_fd('0' + (char)(n % 10) * (n < 0 ? -1 : 1), fd);
	}
}
