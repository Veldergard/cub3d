/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:23:35 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 19:32:35 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds the element ’new’ at the beginning of the
** list.
**
** t_list **lst - The address of a pointer to the first link of
** a list.
** t_list *new - The address of a pointer to the element to be
** added to the list.
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
