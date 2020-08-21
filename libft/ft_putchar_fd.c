/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 01:10:09 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 01:51:57 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs the character ’c’ to the given file
** descriptor.
**
** char c - The character to output.
** int fd - The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
