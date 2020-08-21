/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 01:16:10 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 01:18:14 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs the string ’s’ to the given file
** descriptor.
**
** #1. The string to output.
** #2. The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}
