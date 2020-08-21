/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:33:05 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 19:50:52 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns the last element of the list.
**
** t_list *lst - The beginning of the list.
**
** Last element of the list.
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
