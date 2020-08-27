/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/27 17:41:47 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(char *cub)
{
	t_data		data;

	ft_bzero(&data, sizeof(data));
	data.texture.ceiling = NONE;
	data.texture.floor = NONE;
	cub_parse(cub, &data);
	int i = 0;
	while (data.map.tab[i])
	{
		printf("%s\n", data.map.tab[i++]);
	}
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		ft_init(av[1]);
	else if (ac == 2)
		ft_init(av[1]);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
