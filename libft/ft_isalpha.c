/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:23:08 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 22:27:31 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isalpha()
** checks  for  an  alphabetic  character; in the standard "C" locale, it
** is equivalent to (isupper(c) || islower(c)).  In some locales,
** there may be additional characters for which isalpha() is
** true—letters which are neither uppercase nor lowercase.
**
** int c - character
**
** The values returned are nonzero if the character c falls into
** the tested class, and zero if not.
*/

#include "libft.h"

int		ft_isalpha(int c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1024 : 0);
}
