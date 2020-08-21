/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 21:18:06 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/01 22:21:48 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The  ft_calloc() function allocates memory for an array of nmemb
** elements of size bytes each and returns a pointer to the
** allocated memory. The memory is set to zero. If nmemb or size is 0,
** then ft_calloc() returns either NULL, or a unique pointer value
** that can later be successfully passed to free().
** If the multiplication of nmemb and  size  would  result
** in integer overflow, then ft_calloc() returns an error. By contrast,
** an integer overflow would not be detected in the following call
** to malloc(), with the result that an incorrectly
** sized block of memory would be allocated:
**
** malloc(nmemb * size);
**
** size_t nmemb - amount of elements
** size_t size - single item size
**
** The ft_calloc()  function return a pointer to the allocated memory,
** which is suitably aligned for any built-in type. On error, these
** functions return NULL. NULL may also be returned by a successful
** call to malloc() with a size of zero, or by a successful
** call to ft_calloc() with nmemb or size equal to zero.
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	ptr = malloc(nmemb * size);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}
