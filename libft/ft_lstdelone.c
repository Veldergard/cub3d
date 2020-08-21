/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:51:48 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 19:56:22 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Takes as a parameter an element and frees the
** memory of the element’s content using the function
** ’del’ given as a parameter and free the element.
** The memory of ’next’ must not be freed.
**
** t_list *lst - The element to free.
** void (*del)(void *) - The address of the
** function used to delete the content.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}
