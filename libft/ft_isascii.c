/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:45:17 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 22:27:45 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isascii()
** checks whether c is a 7-bit unsigned char value
** that fits into the ASCII character set.
**
** int c - character
**
** The values returned are nonzero if the character c falls into
** the tested class, and zero if not.
*/

#include "libft.h"

int		ft_isascii(int c)
{
	return ((c >= 0 && c < 128) ? 1 : 0);
}
