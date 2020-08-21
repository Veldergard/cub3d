/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:25:44 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/04 19:50:17 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Counts the number of elements in a list.
**
** t_list *lst - The beginning of the list.
**
** Return length of the list.
*/

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int size;

	if (!lst)
		return (0);
	size = 1;
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
