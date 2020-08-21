/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:58:56 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 18:22:18 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** These functions convert lowercase letters to uppercase, and vice versa.
** If c is a lowercase letter, ft_toupper() returns its uppercase
** equivalent, if an uppercase representation exists in the current
** locale. Otherwise, it returns c.
**
** If c is neither an unsigned char value nor EOF,
** the behavior of these functions is undefined.
**
** c - character
**
** The value returned is that of the converted letter, or
** c if the conversion was not possible.
*/

#include "libft.h"

int		ft_toupper(int c)
{
	if (c >= -128 && c <= -2)
		return (c + 256);
	return (c >= 'a' && c <= 'z' ? c - 32 : c);
}
