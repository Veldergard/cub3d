/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:29:02 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 22:27:42 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isdigit()
** checks for a digit (0 through 9).
**
** int c - character
**
** The values returned are nonzero if the character c falls into
** the tested class, and zero if not.
*/

#include "libft.h"

int		ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9') ? 2048 : 0);
}
