/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:23:10 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 17:01:13 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_bzero() function erases the data in the n bytes of the memory
** starting at the location pointed to by s, by writing zeros (bytes con‐
** taining '\0') to that area.
**
** void *s - memory area
** size_t n - number of bytes to fill
**
** return value - None.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
