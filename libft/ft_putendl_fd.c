/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 01:46:36 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 01:50:28 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs the string ’s’ to the given file
** descriptor, followed by a newline.
**
** #1. The string to output.
** #2. The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}
