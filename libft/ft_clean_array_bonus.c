/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_array_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 17:29:38 by olaurine          #+#    #+#             */
/*   Updated: 2020/05/09 15:56:48 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_clean_array(void **array, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		free(array[i++]);
	free(array);
	return (NULL);
}
