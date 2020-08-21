/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:34:40 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 19:51:26 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds the element ’new’ at the end of the list.
**
** t_list **lst - The address of a pointer to the first link of
** a list.
** t_list *new - The address of a pointer to the element to be
** added to the list.
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *temp;

	if (!lst)
		return ;
	temp = *lst;
	if (!temp)
		*lst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
