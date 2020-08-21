/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:11:05 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 23:00:38 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Iterates the list ’lst’ and applies the function
** ’f’ to the content of each element. Creates a new
** list resulting of the successive applications of
** the function ’f’. The ’del’ function is used to
** delete the content of an element if needed.
**
** t_list *lst - The adress of a pointer to an element.
** void *(*f)(void*) - The adress of the function
** used to iterate on the list.
** void (*del)(void*) - The adress of the function used
** to delete the content of an element if needed.
**
** return the new list. NULL if the allocation fails.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list *result;
	t_list *first;

	if (!lst || !f)
		return (NULL);
	if (!(result = ft_lstnew(f(lst->content))))
		return (NULL);
	first = result;
	while (lst->next)
	{
		lst = lst->next;
		if (!(result->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		result = result->next;
	}
	return (first);
}
