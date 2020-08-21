/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 21:02:39 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/03 18:22:25 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** These functions convert lowercase letters to uppercase, and vice versa.
** If c is an uppercase letter, ft_tolower() returns its lowercase
** equivalent, if a lowercase representation exists in
** the current locale.  Otherwise, it returns c.
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

int		ft_tolower(int c)
{
	if (c >= -128 && c <= -2)
		return (c + 256);
	return (c >= 'A' && c <= 'Z' ? c + 32 : c);
}
