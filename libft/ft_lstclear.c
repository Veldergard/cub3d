/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:56:41 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 21:04:15 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Deletes and frees the given element and every
** successor of that element, using the function ’del’
** and free(3).
** Finally, the pointer to the list must be set to
** NULL.
**
** t_list **lst - The adress of a pointer to an element.
** void (*del)(void*) - The adress of the function
** used to delete the content of the element.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *prev;
	t_list *temp;

	if (!lst)
		return ;
	if (!(temp = *lst))
		return ;
	while (temp->next)
	{
		prev = temp;
		temp = temp->next;
		if (del)
			del(prev->content);
		free(prev);
	}
	if (del)
		del(temp->content);
	free(temp);
	*lst = NULL;
}
