/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:54:33 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 22:27:38 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isprint()
** checks for any printable character including space.
**
** int c - character
**
** The values returned are nonzero if the character c falls into
** the tested class, and zero if not.
*/

#include "libft.h"

int		ft_isprint(int c)
{
	return ((c >= 32 && c <= 126) ? 16384 : 0);
}
