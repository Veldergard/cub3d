/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:43:21 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/15 19:07:25 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop_left(t_list **lst)
{
	void	*result;
	t_list	*temp;

	result = (*lst)->content;
	temp = *lst;
	*lst = (*lst)->next;
	free(temp);
	return (result);
}
